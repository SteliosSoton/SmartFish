#ifndef UNITRIBBON_H
#define UNITRIBBON_H

#include <QWidget>

namespace Ui {class UnitRibbon;}

class UnitRibbon : public QWidget
{
    Q_OBJECT

public:
    explicit UnitRibbon(QWidget *parent = 0);
    ~UnitRibbon();

    Ui::UnitRibbon *ui;

    int getRibbonNumber();

    void setRibbonNumber(int inputNumber);

private:

    int ribbonNumber;

};

#endif // UNITRIBBON_H
