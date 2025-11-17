#ifndef PANTALLANIVEL3_H
#define PANTALLANIVEL3_H

#include <QDialog>

namespace Ui {
class pantallaNivel3;
}

class pantallaNivel3 : public QDialog
{
    Q_OBJECT

public:
    explicit pantallaNivel3(QWidget *parent = nullptr);
    ~pantallaNivel3();

private slots:
    void on_pushButton_clicked();

private:
    Ui::pantallaNivel3 *ui;
};

#endif // PANTALLANIVEL3_H
