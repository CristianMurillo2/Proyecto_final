#include "cannonball.h"
#include <QDebug>
#include <QBrush>
#include <QPen>
#include <QGraphicsEllipseItem>

CannonBall::CannonBall(double x, double y, double v, double a, QGraphicsScene *scene, QObject *parent)
    : QObject(parent), QGraphicsEllipseItem(nullptr)
{
    m_scene = scene;

    m_fisica = new movimientoParticula(x / escala, y / escala, v, a);

    setRect(0, 0, diametro, diametro);
    setBrush(QBrush(Qt::black));
    setPen(QPen(Qt::gray));

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &CannonBall::actualizarPosicion);
    m_timer->start(10);
}

CannonBall::~CannonBall()
{
    if (m_timer) {
        m_timer->stop();
    }
    delete m_fisica;
    for (auto item : m_rastro) {
        if (m_scene) {
            m_scene->removeItem(item);
        }
        delete item;
    }
    m_rastro.clear();
}

void CannonBall::actualizarPosicion()
{
    QPointF currentPos = pos();

    QGraphicsEllipseItem *trailDot = new QGraphicsEllipseItem(currentPos.x(), currentPos.y(), 2, 2);
    trailDot->setBrush(QBrush(Qt::gray));
    trailDot->setPen(Qt::NoPen);

    if (m_scene) {
        m_scene->addItem(trailDot);
        m_rastro.append(trailDot);
    }

    m_fisica->calcularVelocidad();
    m_fisica->calcularPosicion();
    m_fisica->actualizarVelocidad();

    double newX = m_fisica->getPosx();
    double newY = m_fisica->getPosy();

    setPos(newX * escala, -(newY * escala));

    if (newY < 0.0) {
        m_timer->stop();
        qDebug() << "Impacto en X:" << newX;
    }
}

