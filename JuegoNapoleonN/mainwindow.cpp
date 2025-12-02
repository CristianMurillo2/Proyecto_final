#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_stack = new QStackedWidget(this);
    QWidget *menuWidget = ui->centralwidget;
    m_stack->addWidget(menuWidget);
    setCentralWidget(m_stack);

    m_gifAnimacion = new QMovie(":/recursos/PortadaNapoleon.gif");
    m_fondoLabel = new QLabel(this);
    m_fondoLabel->setScaledContents(true);
    m_fondoLabel->resize(this->size());
    m_fondoLabel->lower();
    m_fondoLabel->setMovie(m_gifAnimacion);
    m_gifAnimacion->start();
    this->showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    if (m_fondoLabel) {
        m_fondoLabel->resize(this->size());
    }
    QMainWindow::resizeEvent(event);
}

void MainWindow::on_btnNivel1_clicked()
{
    if (m_gifAnimacion) m_gifAnimacion->stop();
    pantalla1 = new PantallaNivel1(this);
    connect(pantalla1, &PantallaNivel1::regresarAlMenu, this, &MainWindow::volverAlMenuPrincipal);


    m_stack->addWidget(pantalla1);
    m_stack->setCurrentWidget(pantalla1);
    pantalla1->setFocus();
}

void MainWindow::on_btnNivel2_clicked()
{
    if (m_gifAnimacion) m_gifAnimacion->stop();
    pantalla2 = new pantallaNivel2(this);
    connect(pantalla2, &pantallaNivel2::regresarAlMenu, this, &MainWindow::volverAlMenuPrincipal);
    m_stack->addWidget(pantalla2);
    m_stack->setCurrentWidget(pantalla2);
    pantalla2->setFocus();
}

void MainWindow::on_btnNivel3_clicked()
{
    if (m_gifAnimacion) m_gifAnimacion->stop();
    pantalla3 = new PantallaNivel3(this);
    connect(pantalla3, &PantallaNivel3::regresarAlMenu, this, &MainWindow::volverAlMenuPrincipal);
    m_stack->addWidget(pantalla3);
    m_stack->setCurrentWidget(pantalla3);
    pantalla3->setFocus();
}

void MainWindow::centrarVentana()
{
    QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();

    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
}

void MainWindow::volverAlMenuPrincipal()
{
    QWidget *widgetActual = m_stack->currentWidget();
    if (widgetActual != m_stack->widget(0)) {
        m_stack->removeWidget(widgetActual);
        widgetActual->deleteLater();
    }
    m_stack->setCurrentIndex(0);
    if (m_gifAnimacion) m_gifAnimacion->start();
    pantalla1 = nullptr;
    pantalla2 = nullptr;
    pantalla3 = nullptr;
}
