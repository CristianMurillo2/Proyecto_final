#include "pantallanivel1.h"
#include <QGraphicsRectItem>
#include <QHBoxLayout>
#include <QBrush>
#include <QFont>
#include <QRandomGenerator>
#include <QtMath>
#include <algorithm>
#include <QKeyEvent>

PantallaNivel1::PantallaNivel1(QWidget *parent) : QWidget(parent)
{
    this->setFocusPolicy(Qt::StrongFocus);

    //this->setWindowState(Qt::WindowFullScreen);
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    view->setFocusPolicy(Qt::NoFocus);

    musicaFondo = new QMediaPlayer(this);
    salidaAudio = new QAudioOutput(this);
    musicaFondo->setAudioOutput(salidaAudio);
    musicaFondo->setSource(QUrl("qrc:/recursos/Piratas del Caribe.mp3"));
    salidaAudio->setVolume(0.2);
    musicaFondo->setLoops(QMediaPlayer::Infinite);
    musicaFondo->play();

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setSceneRect(0, 0, 1920, 1080);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFrameStyle(QFrame::NoFrame);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(view);
    setLayout(layout);

    crearEscenario();
    crearHUD();

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, jugador, &PersonajeNivel1::actualizarFisica);
    gameTimer->start(16);
    spawnTimer = new QTimer(this);
    connect(spawnTimer, &QTimer::timeout, this, &PantallaNivel1::generarBala);
    spawnTimer->start(2000);
    islaTimer = new QTimer(this);
    connect(islaTimer, &QTimer::timeout, this, &PantallaNivel1::generarIsla);
    islaTimer->start(2500);
    tiempoRestante = 60;
    timerCronometro = new QTimer(this);
    connect(timerCronometro, &QTimer::timeout, this, &PantallaNivel1::actualizarCronometro);
    timerCronometro->start(1000);
}
PantallaNivel1::~PantallaNivel1()
{
    if (musicaFondo) {musicaFondo->stop();}
    if (gameTimer && gameTimer->isActive()) gameTimer->stop();
    if (spawnTimer && spawnTimer->isActive()) spawnTimer->stop();
    if (islaTimer && islaTimer->isActive()) islaTimer->stop();
    if (timerCronometro && timerCronometro->isActive()) timerCronometro->stop();
    if (scene) {scene->clear(); }
}

TipoDisparo PantallaNivel1::obtenerSiguienteDisparo()
{
    if (bolsaDisparos.isEmpty()) {
        bolsaDisparos << LINEAL << PARABOLICO << OSCILANTE << ESPIRAL << ZIGZAG;

        for (int i = 0; i < bolsaDisparos.size(); ++i) {
            int randIndex = QRandomGenerator::global()->bounded(bolsaDisparos.size());
            bolsaDisparos.swapItemsAt(i, randIndex);
        }

    }
    return bolsaDisparos.takeFirst();
}

void PantallaNivel1::crearEscenario()
{
    scene->setSceneRect(0, 0, 800, 600);
    view->setBackgroundBrush(QBrush(QColorConstants::Svg::lightblue));
    jugador = new PersonajeNivel1();
    jugador->setVelocidadMax(8.0);
    jugador->setTamano(70,70);
    jugador->setImagen(":/recursos/barco.png");
    jugador->setPos(375, 450);
    jugador->setZValue(10);
    jugador->setFlag(QGraphicsItem::ItemIsFocusable);
    connect(jugador, &Personaje::personajeMuerto, this, &PantallaNivel1::manejarMuerte);
    scene->addItem(jugador);
    jugador->setFocus();
}

void PantallaNivel1::crearHUD()
{
    textoVida = new QGraphicsTextItem();
    textoVida->setPos(10, 10);
    textoVida->setZValue(50);
    textoVida->setDefaultTextColor(Qt::black);
    textoVida->setFont(QFont("Arial", 14, QFont::Bold));
    scene->addItem(textoVida);

    textoVidas = new QGraphicsTextItem();
    textoVidas->setPos(10, 40);
    textoVidas->setZValue(50);
    textoVidas->setDefaultTextColor(Qt::black);
    textoVidas->setFont(QFont("Arial", 14, QFont::Bold));
    scene->addItem(textoVidas);

    textoCronometro = new QGraphicsTextItem();
    textoCronometro->setPos(350, 10);
    textoCronometro->setZValue(50);
    textoCronometro->setDefaultTextColor(Qt::darkBlue);
    textoCronometro->setFont(QFont("Arial", 20, QFont::Bold));
    textoCronometro->setPlainText("TIEMPO: " + QString::number(tiempoRestante));
    scene->addItem(textoCronometro);

    connect(jugador, &Personaje::vidaCambiada, this, &PantallaNivel1::actualizarVida);
    connect(jugador, &Personaje::vidasCambiadas, this, &PantallaNivel1::actualizarVidas);

    actualizarVida(jugador->getVida());
    actualizarVidas(jugador->getVidasRestantes());
}

void PantallaNivel1::actualizarVida(int vida)
{
    textoVida->setPlainText("Salud: " + QString::number(vida));
}

void PantallaNivel1::actualizarVidas(int vidas)
{
    textoVidas->setPlainText("Vidas: " + QString::number(vidas));
}
void PantallaNivel1::generarBala()
{
    if (!spawnTimer->isActive()) return;
    int x, y;
    qreal px = jugador->x();
    qreal py = jugador->y();
    qreal distancia;
    int distanciaSegura = 200;

    do {
        x = QRandomGenerator::global()->bounded(0, 800);
        y = QRandomGenerator::global()->bounded(0, 500);
        qreal dx = px - x;
        qreal dy = py - y;
        distancia = qSqrt(dx*dx + dy* dy);
    } while (distancia < distanciaSegura);
    qreal dx = px - x;
    qreal dy = py - y;
    if (distancia == 0) distancia = 1;
    qreal velocidadBala = 4.0;
    qreal vx = (dx / distancia) * velocidadBala;
    qreal vy = (dy / distancia) * velocidadBala;

    TipoDisparo tipo = obtenerSiguienteDisparo();

    if (tipo == PARABOLICO) {
        vy -= 5.0;
    }

    BalaCanon *bala = new BalaCanon(x, y, vx, vy, tipo);
    scene->addItem(bala);

    int tiempoAleatorio = QRandomGenerator::global()->bounded(1500, 3000);
    spawnTimer->start(tiempoAleatorio);
}

void PantallaNivel1::manejarMuerte()
{
    int vidasActuales = jugador->getVidasRestantes();
    vidasActuales--;
    jugador->setVidasRestantes(vidasActuales);

    if (vidasActuales > 0) {

        jugador->setVida(100);

        jugador->setPos(375, 450);


        spawnTimer->stop();

        QTimer::singleShot(4000, this, &PantallaNivel1::reanudarSpawns);
    }
    else {
        mostrarGameOver(false);
    }
}
void PantallaNivel1::actualizarCronometro()
{
    tiempoRestante--;
    textoCronometro->setPlainText("TIEMPO: " + QString::number(tiempoRestante));

    if (tiempoRestante <= 0) {
        gameTimer->stop();
        spawnTimer->stop();
        islaTimer->stop();
        timerCronometro->stop();
        mostrarGameOver(true);
    }
}

void PantallaNivel1::reanudarSpawns()
{
    if (jugador->getVidasRestantes() > 0) {
        spawnTimer->start(2000);
    }
}


void PantallaNivel1::generarIsla()
{

    if (!gameTimer->isActive()) return;
    int tamano = QRandomGenerator::global()->bounded(50, 151);
    int x = QRandomGenerator::global()->bounded(0, 800 - tamano);
    qreal velocidad = QRandomGenerator::global()->bounded(2, 6);
    Isla *nuevaIsla = new Isla(x, tamano, velocidad);
    nuevaIsla->setZValue(1);

    scene->addItem(nuevaIsla);
}
void PantallaNivel1::mostrarGameOver(bool ganado)
{
    gameTimer->stop();
    spawnTimer->stop();
    islaTimer->stop();
    if (timerCronometro) timerCronometro->stop();
    if (jugador) jugador->clearFocus();
    if(musicaFondo) {musicaFondo->stop();}

    QRectF bounds = scene->sceneRect();
    QGraphicsRectItem *fondoOscuro = new QGraphicsRectItem(bounds);
    fondoOscuro->setBrush(QColor(0, 0, 0, 150));
    fondoOscuro->setZValue(99);
    scene->addItem(fondoOscuro);
    QString mensaje = ganado ? "¡GANASTE!" : "GAME OVER";
    QColor colorTexto = ganado ? Qt::green : Qt::red;
    QGraphicsSimpleTextItem *textoFinal = new QGraphicsSimpleTextItem(mensaje);
    QFont fuente("Arial", 50, QFont::Bold);
    textoFinal->setFont(fuente);
    textoFinal->setBrush(QBrush(colorTexto));
    textoFinal->setZValue(100);
    QRectF rectTexto = textoFinal->boundingRect();
    QPointF centro = bounds.center();
    textoFinal->setPos(centro.x() - (rectTexto.width() / 2), centro.y() - (rectTexto.height() / 2));
    scene->addItem(textoFinal);
    QTimer::singleShot(3000, this, [this](){
        emit regresarAlMenu();
    });
}

void PantallaNivel1::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        gameTimer->stop();
        spawnTimer->stop();
        islaTimer->stop();
        if (timerCronometro) timerCronometro->stop();
        if (musicaFondo) musicaFondo->stop();
        emit regresarAlMenu();
        return;
    }
    if (jugador) {
        jugador->keyPressEvent(event);
    }
}

void PantallaNivel1::keyReleaseEvent(QKeyEvent *event)
{
    if (jugador) {
        jugador->keyReleaseEvent(event);
    }
}

void PantallaNivel1::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if (view && scene) {
        view->fitInView(scene->sceneRect(), Qt::IgnoreAspectRatio);
    }
}
void PantallaNivel1::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    if (view && scene) {
        view->fitInView(scene->sceneRect(), Qt::IgnoreAspectRatio);
    }
    this->setFocus();
}

