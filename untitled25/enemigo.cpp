#include "enemigo.h"
#include "arma.h"
#include <QtMath>
#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>

Enemigo::Enemigo(PersonajeNivel3* objetivo, QGraphicsItem *parent)
    : QObject(nullptr), QGraphicsPixmapItem(parent), target(objetivo)
{
    QPixmap hojaCompleta("C:\\Users\\crist\\OneDrive\\Escritorio\\proyecto final\\build-untitled25-Desktop_Qt_6_5_3_MinGW_64_bit-Debug\\enemigo.png");

    int x = 540;
    int y = 791;
    int w = 125;
    int h = 196;

    QPixmap skin;
    if (hojaCompleta.isNull()) {
        skin = QPixmap(40, 40); skin.fill(Qt::red);
    } else {
        skin = hojaCompleta.copy(x, y, w, h);
    }

    setPixmap(skin.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setTransformOriginPoint(boundingRect().center());
    vida = 3;
    velocidad = 2.0;
    tiempoVivo = 0;
    estadoActual = ENTRANDO;
    timerIA = new QTimer(this);
    connect(timerIA, &QTimer::timeout, this, &Enemigo::mover);
    timerIA->start(30);

    timerDisparo = new QTimer(this);
    connect(timerDisparo, &QTimer::timeout, this, &Enemigo::disparar);
    timerDisparo->start(QRandomGenerator::global()->bounded(2000, 4000));
}

void Enemigo::recibirDano(int cantidad)
{
    vida -= cantidad;
    if (vida <= 0) {
        emit enemigoMuerto();
        if (scene()) scene()->removeItem(this);
        delete this;
    }
}

void Enemigo::disparar()
{
    if (!target || !scene()) return;

    qreal dx = target->x() - x();
    qreal dy = target->y() - y();

    qreal centroX = x() + boundingRect().width() / 2;
    qreal centroY = y() + boundingRect().height() / 2;
    qreal desfaseX = 25.0;
    qreal desfaseY = 5.0;

    qreal salidaX;
    qreal salidaY = centroY + desfaseY;

    if (dx < 0) {
        salidaX = centroX - desfaseX;
    } else {
        salidaX = centroX + desfaseX;
    }

    salidaX -= 10;
    salidaY -= 10;

    Arma *bala = new Arma(salidaX, salidaY, dx, dy, 40, false, true);

    scene()->addItem(bala);
}
void Enemigo::mover()
{
    if (!target || !scene()) return;

    tiempoVivo++;
    if (tiempoVivo == 200) {
        velocidad += 1.5;
        setOpacity(0.7);
        timerDisparo->setInterval(1500);
    }
    qreal dx = target->x() - x();
    qreal dy = target->y() - y();
    qreal distancia = qSqrt(dx*dx + dy*dy);
    if (dx < 0) setTransform(QTransform::fromScale(-1, 1));
    else setTransform(QTransform());
    qreal vx = 0;
    qreal vy = 0;
    qreal angulo = qAtan2(dy, dx);


    if (estadoActual == ENTRANDO) {
        qreal centroDX = 640 - x();
        qreal centroDY = 360 - y();
        qreal anguloCentro = qAtan2(centroDY, centroDX);

        vx = qCos(anguloCentro) * velocidad;
        vy = qSin(anguloCentro) * velocidad;

        if (x() > 50 && x() < 1230 && y() > 50 && y() < 670) {
            estadoActual = COMBATE;
        }
    }
    else if (estadoActual == COMBATE) {

        qreal anguloJugador = qAtan2(dy, dx);

        if (distancia > 300) {
            vx = qCos(anguloJugador) * velocidad;
            vy = qSin(anguloJugador) * velocidad;
        }
        else if (distancia < 150) {
            vx = -qCos(anguloJugador) * (velocidad * 0.8);
            vy = -qSin(anguloJugador) * (velocidad * 0.8);
        }
        else {

            vx = qCos(anguloJugador + 1.57) * (velocidad * 0.5);
            vy = qSin(anguloJugador + 1.57) * (velocidad * 0.5);
        }
    }
    if (estadoActual == ENTRANDO) {
        setPos(x() + vx, y() + vy);
        return;
    }
    QPointF posOriginal = pos();
    setPos(x() + vx, y() + vy);

    if (chocaConMuro()) {
        setPos(posOriginal);

        setPos(x() + vx, y());
        if (chocaConMuro()) {
            setPos(posOriginal);

            setPos(x(), y() + vy);
            if (chocaConMuro()) {
                setPos(posOriginal);
            }
        }
    }
}
bool Enemigo::chocaConMuro()
{
    QList<QGraphicsItem*> colisiones = collidingItems();
    for (QGraphicsItem *item : colisiones) {
        if (dynamic_cast<QGraphicsRectItem*>(item) && !dynamic_cast<Arma*>(item)) {
            return true;
        }
    }
    return false;
}
