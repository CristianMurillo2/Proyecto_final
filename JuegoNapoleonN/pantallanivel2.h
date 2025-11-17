#ifndef PANTALLANIVEL2_H
#define PANTALLANIVEL2_H

#include <QDialog>

namespace Ui {
class pantallaNivel2;
}

class pantallaNivel2 : public QDialog
{
    Q_OBJECT

public:
    explicit pantallaNivel2(QWidget *parent = nullptr);
    ~pantallaNivel2();

private slots:
    void on_pushButton_clicked();

private:
    Ui::pantallaNivel2 *ui;
};

#endif // PANTALLANIVEL2_H
