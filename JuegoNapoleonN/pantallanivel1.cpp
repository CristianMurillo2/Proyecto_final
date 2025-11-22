#include "pantallanivel1.h"
#include "ui_pantallanivel1.h"

pantallaNivel1::pantallaNivel1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::pantallaNivel1)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

pantallaNivel1::~pantallaNivel1()
{
    delete ui;
}

void pantallaNivel1::on_pushButton_clicked()
{
    this->close();
}

