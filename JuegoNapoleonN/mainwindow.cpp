#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QUrl>
#include "pantallanivel1.h"
#include "pantallanivel2.h"
#include "pantallanivel3.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_player = new QMediaPlayer(this);
    m_audioOutput = new QAudioOutput(this);
    m_videoSink = new QVideoSink(this);

    m_player->setAudioOutput(m_audioOutput);
    m_player->setVideoSink(m_videoSink);

    connect(m_videoSink, &QVideoSink::videoFrameChanged, this, [this](const QVideoFrame &frame){
        m_currentFrame = frame;
        this->update();
    });

    QString rutaVideo = "C:/Users/rgome/OneDrive/Documentos/Qt Informatica 2/Proyecto final/GitHub/JuegoNapoleonN/PortadaNapoleon.mp4";
    m_player->setSource(QUrl::fromLocalFile(rutaVideo));
    m_audioOutput->setVolume(0);
    m_player->setLoops(QMediaPlayer::Infinite);
    m_player->play();

    m_musicaPlayer = new QMediaPlayer(this);
    m_musicaOutput = new QAudioOutput(this);
    m_musicaPlayer->setAudioOutput(m_musicaOutput);

    QString rutaMusica = "C:/Users/rgome/OneDrive/Documentos/Qt Informatica 2/Proyecto final/GitHub/JuegoNapoleonN/mi_musica.mp3";
    m_musicaPlayer->setSource(QUrl::fromLocalFile(rutaMusica));
    m_musicaOutput->setVolume(0.5);
    m_musicaPlayer->setLoops(QMediaPlayer::Infinite);
    m_musicaPlayer->play();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if (m_currentFrame.isValid()) {
        painter.drawImage(rect(), m_currentFrame.toImage());
    } else {
        painter.fillRect(rect(), Qt::black);
    }
}

void MainWindow::on_btnNivel1_clicked()
{

    hide();
    pantalla1 = new pantallaNivel1(this);
    pantalla1->show();
    connect(pantalla1, &QDialog::finished, this, &MainWindow::show);
    pantalla1->show();
}


void MainWindow::on_btnNivel2_clicked()
{
    hide();
    pantalla2 = new pantallaNivel2(this);
    pantalla2->show();
    connect(pantalla2, &QDialog::finished, this, &MainWindow::show);
    pantalla2->show();
}


void MainWindow::on_btnNivel3_clicked()
{
    hide();
    pantalla3 = new pantallaNivel3(this);
    pantalla3->show();
    connect(pantalla3, &QDialog::finished, this, &MainWindow::show);
    pantalla3->show();
}

