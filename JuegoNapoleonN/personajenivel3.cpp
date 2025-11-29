#include "personajenivel3.h"
#include "arma.h"
#include "cajaArma.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QKeyEvent>
#include <QtMath>


PersonajeNivel3::PersonajeNivel3(QGraphicsItem *parent)
    : Personaje(parent), w(false), a(false), s(false), d(false),
    ultimaDirX(0), ultimaDirY(1), puedeDisparar(true)
{
    static QPixmap hojaCompleta(":/recursos/napoleon.png");

    int x = 150;
    int y = 725;
    int w = 148;
    int h = 274;
    QPixmap skin;
    if (hojaCompleta.isNull()) {
        skin = QPixmap(80, 80); skin.fill(Qt::cyan);
    } else {
        skin = hojaCompleta.copy(x, y, w, h);
    }

    setPixmap(skin.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setTransformOriginPoint(boundingRect().center());
    setVelocidadMax(5.0);
    armaActual = NORMAL;
    tiempoCooldown = 400;
    vida = 3;

    timerPoder = new QTimer(this);
    timerPoder->setSingleShot(true);
    connect(timerPoder, &QTimer::timeout, this, &PersonajeNivel3::restaurarArma);

    sonidoDisparo = new QSoundEffect(this);
    sonidoDisparo->setSource(QUrl("qrc:/recursos/pistol-shot-233473.wav"));
    sonidoDisparo->setVolume(0.1f);

    sonidoPowerUp = new QSoundEffect(this);
    sonidoPowerUp->setSource(QUrl("qrc:/recursos/pick-up-sfx-38516.wav"));
    sonidoPowerUp->setVolume(0.1f);
}

void PersonajeNivel3::recibirDano()
{
    vida--;
    emit vidaCambiada(vida);
    setOpacity(0.5);
    QTimer::singleShot(200, [this](){ setOpacity(1.0); });

    if (vida <= 0) {
        emit jugadorMuerto();
    }
}
void PersonajeNivel3::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_W: w = true; break;
    case Qt::Key_S: s = true; break;
    case Qt::Key_A: a = true; break;
    case Qt::Key_D: d = true; break;
    case Qt::Key_C:
        if (puedeDisparar) {
            disparar();
        }
        break;
    }
}

void PersonajeNivel3::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_W: w = false; break;
    case Qt::Key_S: s = false; break;
    case Qt::Key_A: a = false; break;
    case Qt::Key_D: d = false; break;
    }
}

void PersonajeNivel3::actualizarMovimiento()
{
    qreal dx = 0;
    qreal dy = 0;

    if (w) dy -= 1;
    if (s) dy += 1;
    if (a) dx -= 1;
    if (d) dx += 1;

    if (dx < 0) {
        QTransform transform;
        transform.scale(-1, 1);
        qreal desfaseX = 40.0;
        transform.translate(-desfaseX, 0);
        setTransform(transform);
        ultimaDirX = -1;
    } else if (dx > 0) {
        setTransform(QTransform());
    }
    if (dx != 0 || dy != 0) {
        ultimaDirX = dx;
        ultimaDirY = dy;
    }
    qreal moveX = dx * velocidadMax;
    qreal moveY = dy * velocidadMax;
    if (moveX != 0 && canMoveTo(x() + moveX, y())) {
        setPos(x() + moveX, y());
    }
    if (moveY != 0 && canMoveTo(x(), y() + moveY)) {
        setPos(x(), y() + moveY);
    }
}

void PersonajeNivel3::cambiarArma(TipoArma nuevoTipo, int duracionMs)
{
    if (sonidoPowerUp->status() == QSoundEffect::Ready || true) {
        sonidoPowerUp->play();
    }

    armaActual = nuevoTipo;
    switch (armaActual) {
    case METRALLETA: tiempoCooldown = 100; break;
    case SNIPER:     tiempoCooldown = 800; break;
    case ESCOPETA:   tiempoCooldown = 600; break;
    default:         tiempoCooldown = 400; break;
    }

    timerPoder->start(duracionMs);
}

void PersonajeNivel3::restaurarArma()
{
    armaActual = NORMAL;
    tiempoCooldown = 400;
}

void PersonajeNivel3::disparar()
{

    if (!scene()) return;

    if (sonidoDisparo->isPlaying()) {sonidoDisparo->stop();}
    sonidoDisparo->play();

    qreal cx = x() + boundingRect().width() / 2 - 5;
    qreal cy = y() + boundingRect().height() / 2 - 5;
    qreal centroX = x() + boundingRect().width() / 2;
    qreal centroY = y() + boundingRect().height() / 2;
    qreal desfaseX = 2.5;
    qreal desfaseY = -10.0;
    qreal salidaX = centroX;
    qreal salidaY = centroY + desfaseY;
    if (ultimaDirX < 0) {
        salidaX = centroX - desfaseX;
    } else {
        salidaX = centroX + desfaseX;
    }

    salidaX -= 7.5;
    salidaY -= 7.5;
    int rangoNormal = 40;
    int rangoEscopeta = 55;
    int rangoMetralleta = 60;
    int rangoSniper = 90;

    if (armaActual == ESCOPETA) {
        scene()->addItem(new Arma(salidaX, salidaY, ultimaDirX, ultimaDirY, 55, false, false));

        double angulo = 0.3;
        qreal ix = ultimaDirX * qCos(-angulo) - ultimaDirY * qSin(-angulo);
        qreal iy = ultimaDirX * qSin(-angulo) + ultimaDirY * qCos(-angulo);
        scene()->addItem(new Arma(salidaX, salidaY, ix, iy, 55, false, false));

        qreal dx = ultimaDirX * qCos(angulo) - ultimaDirY * qSin(angulo);
        qreal dy = ultimaDirX * qSin(angulo) + ultimaDirY * qCos(angulo);
        scene()->addItem(new Arma(salidaX, salidaY, dx, dy, 55, false, false));
    }
    else if (armaActual == SNIPER) {
        scene()->addItem(new Arma(salidaX, salidaY, ultimaDirX, ultimaDirY, 90, true, false));
    }
    else if (armaActual == METRALLETA) {
        scene()->addItem(new Arma(salidaX, salidaY, ultimaDirX, ultimaDirY, 60, false, false));
    }
    else {
        scene()->addItem(new Arma(salidaX, salidaY, ultimaDirX, ultimaDirY, 40, false, false));
    }
    puedeDisparar = false;
    QTimer::singleShot(tiempoCooldown, [this](){ puedeDisparar = true; });

}

