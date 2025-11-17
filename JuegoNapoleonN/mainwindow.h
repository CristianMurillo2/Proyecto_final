#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QVideoSink>
#include <QVideoFrame>
#include <QPainter>
#include "pantallanivel1.h"
#include "pantallanivel2.h"
#include "pantallanivel3.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_btnNivel1_clicked();

    void on_btnNivel2_clicked();

    void on_btnNivel3_clicked();

private:
    Ui::MainWindow *ui;

    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;
    QVideoSink *m_videoSink;
    QVideoFrame m_currentFrame;

    QMediaPlayer *m_musicaPlayer;
    QAudioOutput *m_musicaOutput;

    pantallaNivel1 *pantalla1;
    pantallaNivel2 *pantalla2;
    pantallaNivel3 *pantalla3;
};

#endif // MAINWINDOW_H
