#include "pantallanivel3.h"
#include <QGraphicsRectItem>
#include <QHBoxLayout>
#include <QBrush>
#include <QRandomGenerator>

PantallaNivel3::PantallaNivel3(QWidget *parent) : QWidget(parent)
{
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(1280, 720);

    QHBoxLayout *layout = new QHBoxLayout(this);
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
    musicaFondo->setSource(QUrl::fromLocalFile("MA_Pereveslo_We_Are_All_Leaders.wav"));
    musicaFondo->setVolume(0.0f);
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

void PantallaNivel3::crearEscenario()
{
    int ancho = 1280;
    int alto = 720;
    scene->setSceneRect(0, 0, ancho, alto);
    QPixmap imagenFondo("C:\\Users\\crist\\OneDrive\\Escritorio\\proyecto final\\build-untitled25-Desktop_Qt_6_5_3_MinGW_64_bit-Debug\\fondo.png");

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

    int largoL = 150;
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
    if (bolsaArmas.isEmpty()) {
        rellenarBolsa();
    }

        bool encontrado = false;
        for (int i = 1; i < bolsaArmas.size(); ++i) {
            if (bolsaArmas[i] != ultimaArmaGenerada) {
                bolsaArmas.swapItemsAt(0, i);
                encontrado = true;
                break;
            }
        }
    TipoArma tipoSeleccionado = bolsaArmas.takeFirst();
    ultimaArmaGenerada = tipoSeleccionado;

    int margen = 60;
    int x = QRandomGenerator::global()->bounded(margen, 1280 - margen);
    int y = QRandomGenerator::global()->bounded(margen, 720 - margen);

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

    QGraphicsTextItem *textoGO = new QGraphicsTextItem("GAME OVER");
    QFont fuente("Arial", 50, QFont::Bold);
    textoGO->setFont(fuente);
    textoGO->setDefaultTextColor(Qt::red);
    textoGO->setZValue(100);

    qreal tx = (1280 - textoGO->boundingRect().width()) / 2;
    qreal ty = (720 - textoGO->boundingRect().height()) / 2;
    textoGO->setPos(tx, ty);

    scene->addItem(textoGO);
}
void PantallaNivel3::actualizarContadorVida(int vida)
{
    textoVida->setPlainText("Salud: " + QString::number(vida));
        if (vida == 1) {
        textoVida->setDefaultTextColor(Qt::darkRed);
    }
}
