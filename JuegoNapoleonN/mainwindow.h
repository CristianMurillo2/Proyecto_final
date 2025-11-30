#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMovie>
#include <QLabel>
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
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_btnNivel1_clicked();

    void on_btnNivel2_clicked();

    void on_btnNivel3_clicked();

private:
    Ui::MainWindow *ui;
    QMovie *m_gifAnimacion;
    QLabel *m_fondoLabel;
    PantallaNivel1 *pantalla1;
    pantallaNivel2 *pantalla2;
    PantallaNivel3 *pantalla3;
    void centrarVentana();
};

#endif // MAINWINDOW_H
