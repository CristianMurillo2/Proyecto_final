#include "pantallanivel2.h"
#include "ui_pantallanivel2.h"

pantallaNivel2::pantallaNivel2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::pantallaNivel2)
    , m_scene(nullptr)
    , cannon(nullptr)
    , base(nullptr)
{
    ui->setupUi(this);
    this->setFocusPolicy(Qt::StrongFocus);

    m_anguloGrados = ui->verticalSlider->value();
    ui->lblAngulo->setText(QString("%01°").arg(m_anguloGrados, 0, 'f', 0));

    m_scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(m_scene);
    m_scene->setSceneRect(0, 0, 1145, 746);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    if (layout()) {
        layout()->setContentsMargins(0, 0, 0, 0);
    }
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->graphicsView->setFocusPolicy(Qt::NoFocus);

    timerColisiones = new QTimer(this);
    connect(timerColisiones, &QTimer::timeout, this, &pantallaNivel2::verificarColisiones);

    timerJuego = new QTimer(this);
    connect(timerJuego, &QTimer::timeout, this, &pantallaNivel2::actualizarCronometro);

    sonidoDisparo = new QSoundEffect(this);
    sonidoDisparo->setSource(QUrl("qrc:/recursos/pistol-shot-233473.wav"));
    sonidoDisparo->setVolume(0.1f);

    iniciarNivel();
}

pantallaNivel2::~pantallaNivel2()
{
    if (musicaFondo) musicaFondo->stop();
    if (timerColisiones) timerColisiones->stop();
    if (timerJuego->isActive()) timerJuego->stop();
    qDeleteAll(m_balas);
    m_balas.clear();

    if (m_scene) m_scene->clear();
    delete ui;
}

void pantallaNivel2::iniciarNivel(){

    m_scene->clear();
    m_balas.clear();
    cannon = nullptr;
    base = nullptr;
    obst.clear();
    tiempoRestante = 40;

    QImage imagen(":/recursos/fondo nivel-2.jpeg");
    QBrush fondo(imagen);
    m_scene->setBackgroundBrush(fondo);

    QPixmap pixMap(":/recursos/cannon2-2.png");
    cannon = new QGraphicsPixmapItem();
    m_scene -> addItem(cannon);
    cannon -> setPixmap(pixMap);
    cannon -> setScale(0.25);
    cannon -> setPos(30,-150);

    musicaFondo = new QMediaPlayer(this);
    salidaAudio = new QAudioOutput(this);

    musicaFondo->setAudioOutput(salidaAudio);
    musicaFondo->setSource(QUrl("qrc:/recursos/musicaNivel2.mp3"));
    salidaAudio->setVolume(0.1);
    musicaFondo->setLoops(QMediaPlayer::Infinite);
    musicaFondo->play();

    QPixmap pixMap2(":/recursos/base.png");
    base = new QGraphicsPixmapItem();
    m_scene -> addItem(base);
    base -> setPixmap(pixMap2);
    base -> setPos(1680,-715);

    QPixmap pixMap3(":/recursos/bandera de francia.png");
    banderaF = new QGraphicsPixmapItem();
    m_scene -> addItem(banderaF);
    banderaF -> setPixmap(pixMap3);
    banderaF ->setScale(0.25);
    banderaF -> setPos(0,-205);

    QPixmap pixMap4(":/recursos/bandera britanica.png");
    banderaB = new QGraphicsPixmapItem();
    m_scene -> addItem(banderaB);
    banderaB -> setPixmap(pixMap4);
    banderaB ->setScale(0.25);
    banderaB -> setPos(1655,-835);

    QPixmap imagenOriginal(":/recursos/tienda de campana1.png");
    QPixmap imagenEscalada = imagenOriginal.scaled(100, 67, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    for (int i = 0; i < 4; ++i) {
        QGraphicsPixmapItem* tienda = new QGraphicsPixmapItem(imagenEscalada);
        tienda->setPos(1260 + (i * 150), -120);
        m_scene->addItem(tienda);
        obst.append(tienda);
    }

    for (int i = 0; i < 5; ++i) {
        QGraphicsPixmapItem* tienda = new QGraphicsPixmapItem(imagenEscalada);
        tienda->setPos(1710 , -203 - (i * 106));
        m_scene->addItem(tienda);
        obst.append(tienda);
    }



    int width = this->width();
    int height = this->height();
    m_scene->setSceneRect(0, -height, width, height);

    textoCronometro = new QGraphicsTextItem();
    textoCronometro->setFont(QFont("Arial", 50, QFont::Bold));
    textoCronometro->setDefaultTextColor(Qt::black);
    textoCronometro->setPlainText(QString::number(tiempoRestante));
    textoCronometro->setZValue(200);
    m_scene->addItem(textoCronometro);

    imagenTiendaNormal.load(":/recursos/tienda de campana1.png");
    imagenTiendaNormal = imagenTiendaNormal.scaled(100, 67, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    imagenTiendaRota.load(":/recursos/tienda2.png");
    imagenTiendaRota = imagenTiendaRota.scaled(100, 67, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    if (timerColisiones->isActive()) timerColisiones->stop();
    timerColisiones->start(30);
    if (timerJuego->isActive()) timerJuego->stop();
    timerJuego->start(1000);

}

void pantallaNivel2::on_btnDisparar_clicked()
{
    if (m_balas.size() >= 3) {
        return;
    }
    if (sonidoDisparo) {
        sonidoDisparo->play();
    }
    double velocidad_inicial = 35.0;
    double angulo_rad = m_anguloGrados * (M_PI / 180.0);
    CannonBall *nuevaBola = new CannonBall(140, 120, velocidad_inicial, angulo_rad, m_scene, this);
    m_scene->addItem(nuevaBola);
    m_balas.append(nuevaBola);

    QPixmap pixMap1(":/recursos/humo.png");
    QGraphicsPixmapItem *humo = new QGraphicsPixmapItem();
    m_scene -> addItem(humo);
    humo -> setPixmap(pixMap1);
    humo -> setScale(0.25);
    humo -> setPos(120,-170);
    QTimer::singleShot(1000, this, [this, humo]() {
        if (m_scene && humo && m_scene->items().contains(humo)) {
            m_scene->removeItem(humo);
            delete humo;
        }
    });
}

void pantallaNivel2::on_verticalSlider_valueChanged(int value)
{
    m_anguloGrados = static_cast<double>(value);
    ui->lblAngulo->setText(QString("%1°").arg(m_anguloGrados, 0, 'f', 0));
}

void pantallaNivel2::verificarColisiones()
{
    double limiteSuelo = 0;
    double limiteDerecha = m_scene->sceneRect().width() + 700;
    for (int i = m_balas.size() - 1; i >= 0; --i) {
        CannonBall *b = m_balas[i];
        bool balaEliminada = false;
        if (b->y() > limiteSuelo || b->x() > limiteDerecha || b->x() < -50) {
            m_scene->removeItem(b);
            delete b;
            b = nullptr;
            m_balas.removeAt(i);
            balaEliminada = true;
        }

        if (balaEliminada) continue;
        for (int j = 0; j < obst.size(); ++j) {
            if (b->collidesWithItem(obst[j])) {
                QPointF posicionTienda = obst[j]->pos();
                m_scene->removeItem(obst[j]);
                delete obst[j];
                obst.removeAt(j);
                QGraphicsPixmapItem *roto = new QGraphicsPixmapItem(imagenTiendaRota);
                roto->setPos(posicionTienda);
                m_scene->addItem(roto);
                m_scene->removeItem(b);
                delete b;
                b = nullptr;
                m_balas.removeAt(i);
                balaEliminada = true;
                break;
            }
        }
    }
    if (obst.isEmpty()) {
        finalizarJuego(true);
    }
}

void pantallaNivel2::actualizarCronometro()
{
    tiempoRestante--;
    if (textoCronometro) {
        textoCronometro->setPlainText(QString::number(tiempoRestante));
        if (tiempoRestante <= 10) {
            textoCronometro->setDefaultTextColor(Qt::red);
        } else {
            textoCronometro->setDefaultTextColor(Qt::green);
        }
        QRect viewportRect = ui->graphicsView->viewport()->rect();
        QRectF visibleSceneRect = ui->graphicsView->mapToScene(viewportRect).boundingRect();
        double tx = visibleSceneRect.center().x() - (textoCronometro->boundingRect().width() / 2);
        double ty = visibleSceneRect.top() + 20;
        textoCronometro->setPos(tx, ty);
    }
    if (tiempoRestante <= 0) {
        finalizarJuego(false);
    }

}

void pantallaNivel2::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        if (musicaFondo) musicaFondo->stop();
        if (timerJuego) timerJuego->stop();
        if (timerColisiones) timerColisiones->stop();
        emit regresarAlMenu();
        return;
    }
    if (event->key() == Qt::Key_W) {
        int valorActual = ui->verticalSlider->value();
        ui->verticalSlider->setValue(valorActual + 1);
    }
    else if (event->key() == Qt::Key_S) {
        int valorActual = ui->verticalSlider->value();
        ui->verticalSlider->setValue(valorActual - 1);
    }
    else if (event->key() == Qt::Key_Space) {
        on_btnDisparar_clicked();
    }
    else {
        QWidget::keyPressEvent(event);
    }
}

void pantallaNivel2::finalizarJuego(bool ganado)
{
    if (musicaFondo) {musicaFondo->stop();}
    if (timerJuego->isActive()) timerJuego->stop();
    if (timerColisiones->isActive()) timerColisiones->stop();
    QGraphicsRectItem *fondoOscuro = new QGraphicsRectItem(-2000, -2000, 5000, 5000);
    fondoOscuro->setBrush(QColor(0, 0, 0, 150));
    fondoOscuro->setZValue(99);
    m_scene->addItem(fondoOscuro);
    QString mensaje = ganado ? "¡GANASTE!" : "GAME OVER";
    QColor colorTexto = ganado ? Qt::green : Qt::red;
    QGraphicsSimpleTextItem *textoFinal = new QGraphicsSimpleTextItem(mensaje);
    QFont fuente("Arial", 50, QFont::Bold);
    textoFinal->setFont(fuente);
    textoFinal->setBrush(QBrush(colorTexto));
    textoFinal->setZValue(100);
    m_scene->addItem(textoFinal);
    QRect viewportRect = ui->graphicsView->viewport()->rect();
    QPoint centroVentana = viewportRect.center();
    QPointF centroEscena = ui->graphicsView->mapToScene(centroVentana);
    QRectF rectTexto = textoFinal->boundingRect();
    textoFinal->setPos(centroEscena.x() - (rectTexto.width() / 2), centroEscena.y() - (rectTexto.height() / 2));
    QTimer::singleShot(3000, this, [this](){
        emit regresarAlMenu();
    });
}
