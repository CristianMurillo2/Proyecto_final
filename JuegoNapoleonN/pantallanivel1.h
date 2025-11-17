#ifndef PANTALLANIVEL1_H
#define PANTALLANIVEL1_H

#include <QDialog>

namespace Ui {
class pantallaNivel1;
}

class pantallaNivel1 : public QDialog
{
    Q_OBJECT

public:
    explicit pantallaNivel1(QWidget *parent = nullptr);
    ~pantallaNivel1();

private slots:
    void on_pushButton_clicked();

private:
    Ui::pantallaNivel1 *ui;
};

#endif // PANTALLANIVEL1_H
