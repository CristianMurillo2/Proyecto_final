#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QVideoSink>
#include <QVideoFrame>
#include <QPainter>

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

private:
    Ui::MainWindow *ui;

    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;
    QVideoSink *m_videoSink;
    QVideoFrame m_currentFrame;

    QMediaPlayer *m_musicaPlayer;
    QAudioOutput *m_musicaOutput;
};

#endif // MAINWINDOW_H
