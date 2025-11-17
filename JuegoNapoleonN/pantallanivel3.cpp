#include "pantallanivel3.h"
#include "ui_pantallanivel3.h"

pantallaNivel3::pantallaNivel3(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::pantallaNivel3)
{
    ui->setupUi(this);
}

pantallaNivel3::~pantallaNivel3()
{
    delete ui;
}

void pantallaNivel3::on_pushButton_clicked()
{
    this->close();
}

