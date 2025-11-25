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
    QPixmap skin(40, 40); skin.fill(Qt::transparent); QPainter p(&skin);
    p.setBrush(Qt::cyan); p.setPen(QPen(Qt::black, 2)); p.drawRect(2, 2, 36, 36); p.end();
    setPixmap(skin);
    setVelocidadMax(5.0);

    armaActual = NORMAL;
    tiempoCooldown = 400;
    vida = 3;

    timerPoder = new QTimer(this);
    timerPoder->setSingleShot(true);
    connect(timerPoder, &QTimer::timeout, this, &PersonajeNivel3::restaurarArma);

    sonidoDisparo = new QSoundEffect(this);
    sonidoDisparo->setSource(QUrl::fromLocalFile("pistol-shot-233473.wav"));
    sonidoDisparo->setVolume(0.5f);

    sonidoPowerUp = new QSoundEffect(this);
    sonidoPowerUp->setSource(QUrl::fromLocalFile("pick-up-sfx-38516.wav"));
    sonidoPowerUp->setVolume(1.0f);
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

    if (sonidoDisparo->isPlaying()) sonidoDisparo->stop();
    sonidoDisparo->play();

    qreal cx = x() + boundingRect().width() / 2 - 5;
    qreal cy = y() + boundingRect().height() / 2 - 5;
    int rangoNormal = 40;
    int rangoEscopeta = 55;
    int rangoMetralleta = 60;
    int rangoSniper = 90;

    if (armaActual == ESCOPETA) {
        scene()->addItem(new Arma(cx, cy, ultimaDirX, ultimaDirY, rangoEscopeta, false, false));
        double angulo = 0.3;
        qreal izqX = ultimaDirX * qCos(-angulo) - ultimaDirY * qSin(-angulo);
        qreal izqY = ultimaDirX * qSin(-angulo) + ultimaDirY * qCos(-angulo);
        scene()->addItem(new Arma(cx, cy, izqX, izqY, rangoEscopeta, false, false));
        qreal derX = ultimaDirX * qCos(angulo) - ultimaDirY * qSin(angulo);
        qreal derY = ultimaDirX * qSin(angulo) + ultimaDirY * qCos(angulo);
        scene()->addItem(new Arma(cx, cy, derX, derY, rangoEscopeta, false, false));
    }
    else if (armaActual == SNIPER) {
        scene()->addItem(new Arma(cx, cy, ultimaDirX, ultimaDirY, rangoSniper, true, false));
    }
    else if (armaActual == METRALLETA) {
        scene()->addItem(new Arma(cx, cy, ultimaDirX, ultimaDirY, rangoMetralleta, false, false));
    }
    else {
        scene()->addItem(new Arma(cx, cy, ultimaDirX, ultimaDirY, rangoNormal, false, false));
    }

    puedeDisparar = false;
    QTimer::singleShot(tiempoCooldown, [this](){ puedeDisparar = true; });
}

