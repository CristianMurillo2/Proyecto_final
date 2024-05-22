#ifndef VENTANAS_H
#define VENTANAS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class ventanas;
}
QT_END_NAMESPACE

class ventanas : public QMainWindow
{
    Q_OBJECT

public:
    ventanas(QWidget *parent = nullptr);
    ~ventanas();

private:
    Ui::ventanas *ui;
};
#endif // VENTANAS_H
