#include "pantallanivel3.h"
#include <QGraphicsRectItem>
#include <QHBoxLayout>
#include <QBrush>
#include <QRandomGenerator>
#include <QDialog>
#include <QResizeEvent>

PantallaNivel3::PantallaNivel3(QWidget *parent) : QDialog(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);

    this->setWindowState(Qt::WindowFullScreen);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1280, 720);
    view = new QGraphicsView(scene, this);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(view);
    setLayout(layout);

    crearEscenario();

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, jugador, &PersonajeNivel3::actualizarMovimiento);
    gameTimer->start(16);
    ultimaArmaGenerada = NORMAL;
    rellenarBolsa();

    timerItems = new QTimer(this);
    connect(timerItems, &QTimer::timeout, this, &PantallaNivel3::generarCajaArma);
    timerItems->start(10000);
    musicaFondo = new QSoundEffect(this);
    musicaFondo->setSource(QUrl("qrc:/recursos/MA_Pereveslo_We_Are_All_Leaders.wav"));
    musicaFondo->setVolume(0.1f);
    musicaFondo->setLoopCount(QSoundEffect::Infinite);
    musicaFondo->play();
    connect(jugador, &PersonajeNivel3::jugadorMuerto, this, &PantallaNivel3::detenerJuego);
    oleadaActual = 0;
    enemigosVivos = 0;
    enemigosPorGenerar = 0;
    timerSpawns = new QTimer(this);
    connect(timerSpawns, &QTimer::timeout, this, &PantallaNivel3::generarEnemigo);
    QTimer::singleShot(1000, this, &PantallaNivel3::iniciarNuevaOleada);
    textoOleada = new QGraphicsTextItem();
    textoOleada->setDefaultTextColor(Qt::white);
    textoOleada->setFont(QFont("Arial", 20, QFont::Bold));
    textoOleada->setZValue(10);
    textoOleada->setPos(1050, 20);
    scene->addItem(textoOleada);
    textoVida = new QGraphicsTextItem();
    textoVida->setDefaultTextColor(Qt::red);
    textoVida->setFont(QFont("Arial", 20, QFont::Bold));
    textoVida->setZValue(10);
    textoVida->setPos(20, 20);
    scene->addItem(textoVida);
    textoVida->setPlainText("Salud: 3");
    connect(jugador, &PersonajeNivel3::jugadorMuerto, this, &PantallaNivel3::detenerJuego);
    connect(jugador, &PersonajeNivel3::vidaCambiada, this, &PantallaNivel3::actualizarContadorVida);
    textoOleada->setPlainText("Oleada: 0 / 5");
}

PantallaNivel3::~PantallaNivel3()
{
    if (gameTimer->isActive()) gameTimer->stop();
    if (timerItems->isActive()) timerItems->stop();
    if (timerSpawns->isActive()) timerSpawns->stop();
    if (musicaFondo) {musicaFondo->stop();}
    if(jugador) jugador->clearFocus();
    if(scene) scene->clear();
    qDebug() << "Nivel 3 destruido correctamente.";
}

void PantallaNivel3::crearEscenario()
{
    int ancho = 1280;
    int alto = 720;
    scene->setSceneRect(0, 0, ancho, alto);
    QPixmap imagenFondo(":/recursos/mapanivel3.jpeg");

    if (imagenFondo.isNull()) {
        view->setBackgroundBrush(QBrush(QColor(50, 50, 60)));
    }
    else {
        imagenFondo = imagenFondo.scaled(ancho, alto, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QGraphicsPixmapItem *itemFondo = new QGraphicsPixmapItem(imagenFondo);

        itemFondo->setPos(0, 0);
        itemFondo->setZValue(-100);
        scene->addItem(itemFondo);
    }

    jugador = new PersonajeNivel3();
    jugador->setPos(ancho/2 - 20, alto/2 - 20);
    jugador->setFlag(QGraphicsItem::ItemIsFocusable);
    scene->addItem(jugador);
    jugador->setFocus();

    QBrush colorMuro(QColor(100, 100, 100));
    QPen bordeMuro(Qt::black, 2);

    int grosor = 40;
    int tamHueco = 150;

    scene->addRect(0, 0, (ancho/2 - tamHueco/2), grosor, bordeMuro, colorMuro);
    scene->addRect((ancho/2 + tamHueco/2), 0, (ancho/2 - tamHueco/2), grosor, bordeMuro, colorMuro);

    scene->addRect(0, alto - grosor, (ancho/2 - tamHueco/2), grosor, bordeMuro, colorMuro);
    scene->addRect((ancho/2 + tamHueco/2), alto - grosor, (ancho/2 - tamHueco/2), grosor, bordeMuro, colorMuro);

    scene->addRect(0, 0, grosor, (alto/2 - tamHueco/2), bordeMuro, colorMuro);
    scene->addRect(0, (alto/2 + tamHueco/2), grosor, (alto/2 - tamHueco/2), bordeMuro, colorMuro);

    scene->addRect(ancho - grosor, 0, grosor, (alto/2 - tamHueco/2), bordeMuro, colorMuro);
    scene->addRect(ancho - grosor, (alto/2 + tamHueco/2), grosor, (alto/2 - tamHueco/2), bordeMuro, colorMuro);

    int largoL = 120;
    int grosorL = 40;

    int centroX = ancho / 2;
    int centroY = alto / 2;
    int separacion = 100;

    scene->addRect(centroX - separacion - grosorL, centroY - separacion - largoL, grosorL, largoL, bordeMuro, colorMuro);
    scene->addRect(centroX - separacion - largoL, centroY - separacion - grosorL, largoL, grosorL, bordeMuro, colorMuro);

    scene->addRect(centroX + separacion, centroY - separacion - largoL, grosorL, largoL, bordeMuro, colorMuro);
    scene->addRect(centroX + separacion, centroY - separacion - grosorL, largoL, grosorL, bordeMuro, colorMuro);

    scene->addRect(centroX - separacion - grosorL, centroY + separacion, grosorL, largoL, bordeMuro, colorMuro);
    scene->addRect(centroX - separacion - largoL, centroY + separacion, largoL, grosorL, bordeMuro, colorMuro);

    scene->addRect(centroX + separacion, centroY + separacion, grosorL, largoL, bordeMuro, colorMuro);
    scene->addRect(centroX + separacion, centroY + separacion, largoL, grosorL, bordeMuro, colorMuro);
}

void PantallaNivel3::rellenarBolsa()
{
    bolsaArmas.clear();
    bolsaArmas.append(ESCOPETA);
    bolsaArmas.append(SNIPER);
    bolsaArmas.append(METRALLETA);

    while (bolsaArmas.size() < 5) {
        int r = QRandomGenerator::global()->bounded(1, 4);
        bolsaArmas.append(static_cast<TipoArma>(r));
    }

    for (int i = 0; i < bolsaArmas.size(); ++i) {
        int randIndex = QRandomGenerator::global()->bounded(bolsaArmas.size());
        bolsaArmas.swapItemsAt(i, randIndex);
    }
}

void PantallaNivel3::generarCajaArma()
{
    int cajasEnEscena = 0;
    QList<QGraphicsItem*> todosLosItems = scene->items();

    for (QGraphicsItem *item : todosLosItems) {
        if (dynamic_cast<CajaArma*>(item)) {
            cajasEnEscena++;
        }
    }

    if (cajasEnEscena >= 2) {
        int tiempoEspera = QRandomGenerator::global()->bounded(3000, 6000);
        timerItems->start(tiempoEspera);
        return;
    }
    int margen = 60;
    int x = 0;
    int y = 0;
    bool posicionValida = false;
    int intentos = 0;
    while (!posicionValida && intentos < 10) {
        x = QRandomGenerator::global()->bounded(margen, 1280 - margen);
        y = QRandomGenerator::global()->bounded(margen, 720 - margen);
        QRectF areaCaja(x, y, 40, 40);
        QList<QGraphicsItem*> colisiones = scene->items(areaCaja);

        bool chocaConMuro = false;

        for (QGraphicsItem *item : colisiones) {
            if (dynamic_cast<QGraphicsRectItem*>(item)) {
                chocaConMuro = true;
                break;
            }
        }

        if (!chocaConMuro) {
            posicionValida = true;
        }

        intentos++;
    }

    if (!posicionValida) {
        timerItems->start(1000);
        return;
    }
    if (bolsaArmas.isEmpty()) {
        rellenarBolsa();
    }

    if (bolsaArmas.first() == ultimaArmaGenerada) {
        for (int i = 1; i < bolsaArmas.size(); ++i) {
            if (bolsaArmas[i] != ultimaArmaGenerada) {
                bolsaArmas.swapItemsAt(0, i);
                break;
            }
        }
    }

    TipoArma tipoSeleccionado = bolsaArmas.takeFirst();
    ultimaArmaGenerada = tipoSeleccionado;

    CajaArma *caja = new CajaArma(x, y, tipoSeleccionado);
    scene->addItem(caja);

    int tiempoAleatorio = QRandomGenerator::global()->bounded(5000, 15001);
    timerItems->start(tiempoAleatorio);
}
void PantallaNivel3::iniciarNuevaOleada()
{
    oleadaActual++;
    enemigosPorGenerar = 1 + (oleadaActual * 2);
    textoOleada->setPlainText("Oleada: " + QString::number(oleadaActual) + " / 5");

    if (enemigosPorGenerar > 20) enemigosPorGenerar = 20;
    qDebug() << ">>> INICIANDO OLEADA" << oleadaActual;
    timerSpawns->start(1500);
}

void PantallaNivel3::generarEnemigo()
{
    if (enemigosPorGenerar <= 0) {
        timerSpawns->stop();
        return;
    }

    int hueco = QRandomGenerator::global()->bounded(1, 5);

    int spawnX = 0;
    int spawnY = 0;

    int ancho = 1280;
    int alto = 720;
    int mitadX = ancho / 2;
    int mitadY = alto / 2;

    switch (hueco) {
    case 1:
        spawnX = mitadX;
        spawnY = -60;
        break;
    case 2:
        spawnX = mitadX;
        spawnY = alto + 60;
        break;
    case 3:
        spawnX = -60;
        spawnY = mitadY;
        break;
    case 4:
        spawnX = ancho + 60;
        spawnY = mitadY;
        break;
    }

    Enemigo *nuevoEnemigo = new Enemigo(jugador);
    nuevoEnemigo->setPos(spawnX, spawnY);
    scene->addItem(nuevoEnemigo);
    connect(nuevoEnemigo, &Enemigo::enemigoMuerto, this, &PantallaNivel3::enemigoEliminado);

    enemigosVivos++;
    enemigosPorGenerar--;
}

void PantallaNivel3::enemigoEliminado()
{
    enemigosVivos--;
    if (enemigosVivos <= 0 && enemigosPorGenerar <= 0) {
        if (oleadaActual >= 5) {
            mostrarVictoria();
        }
        else {
            qDebug() << "Oleada" << oleadaActual << "completada. Descanso...";
            QTimer::singleShot(3000, this, &PantallaNivel3::iniciarNuevaOleada);
        }
    }
}

void PantallaNivel3::mostrarVictoria()
{
    gameTimer->stop();
    timerItems->stop();
    timerSpawns->stop();

    jugador->clearFocus();

    QGraphicsRectItem *fondo = new QGraphicsRectItem(0, 0, 1280, 720);
    fondo->setBrush(QBrush(QColor(0, 255, 0, 100)));
    fondo->setZValue(100);
    scene->addItem(fondo);

    QGraphicsTextItem *textoWin = new QGraphicsTextItem("¡MISIÓN CUMPLIDA!\nSobreviviste 5 Oleadas");
    QFont fuente("Arial", 40, QFont::Bold);
    textoWin->setFont(fuente);
    textoWin->setDefaultTextColor(Qt::white);
    textoWin->setZValue(101);
        qreal tx = (1280 - textoWin->boundingRect().width()) / 2;
    qreal ty = (720 - textoWin->boundingRect().height()) / 2;
    textoWin->setPos(tx, ty);

    scene->addItem(textoWin);
}

void PantallaNivel3::detenerJuego()
{
    gameTimer->stop();
    timerItems->stop();
    timerSpawns->stop();
    if(musicaFondo) musicaFondo->stop();
    jugador->clearFocus();

    QGraphicsTextItem *textoGO = new QGraphicsTextItem("GAME OVER");
    QFont fuente("Arial", 50, QFont::Bold);
    textoGO->setFont(fuente);
    textoGO->setDefaultTextColor(Qt::red);
    textoGO->setZValue(100);
    qreal tx = (1280 - textoGO->boundingRect().width()) / 2;
    qreal ty = (720 - textoGO->boundingRect().height()) / 2;
    textoGO->setPos(tx, ty);
    scene->addItem(textoGO);
    QTimer::singleShot(3000, this, [this](){this->close();});
}

void PantallaNivel3::actualizarContadorVida(int vida)
{
    textoVida->setPlainText("Salud: " + QString::number(vida));
        if (vida == 1) {
        textoVida->setDefaultTextColor(Qt::darkRed);
    }
}

void PantallaNivel3::resizeEvent(QResizeEvent *event)
{
    if (view && scene) {
        view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    }
    QDialog::resizeEvent(event);
}
