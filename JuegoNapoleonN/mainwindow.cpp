#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QUrl>

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

    QString rutaVideo = "C:/Users/rgome/OneDrive/Documentos/Qt Informatica 2/Proyecto final/JuegoNapoleonN/PortadaNapoleon.mp4";
    m_player->setSource(QUrl::fromLocalFile(rutaVideo));
    m_audioOutput->setVolume(0);
    m_player->setLoops(QMediaPlayer::Infinite);
    m_player->play();

    m_musicaPlayer = new QMediaPlayer(this);
    m_musicaOutput = new QAudioOutput(this);
    m_musicaPlayer->setAudioOutput(m_musicaOutput);

    QString rutaMusica = "C:/Users/rgome/OneDrive/Documentos/Qt Informatica 2/Proyecto final/JuegoNapoleonN/mi_musica.mp3";
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
