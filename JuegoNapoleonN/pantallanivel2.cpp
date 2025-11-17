#include "pantallanivel2.h"
#include "ui_pantallanivel2.h"

pantallaNivel2::pantallaNivel2(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::pantallaNivel2)
{
    ui->setupUi(this);
}

pantallaNivel2::~pantallaNivel2()
{
    delete ui;
}

void pantallaNivel2::on_pushButton_clicked()
{
    this->close();
}

