#ifndef UNITRIBBON_H
#define UNITRIBBON_H

#include <QWidget>
#include "biobloomunit.h"

namespace Ui {class UnitRibbon;}

class BioBloomUnit;
class UnitRibbon : public QWidget
{
    Q_OBJECT

public:
    explicit UnitRibbon(BioBloomUnit* inputParentUnit, QWidget *parent = 0);
    ~UnitRibbon();

    Ui::UnitRibbon *ui;

    void updateData();

    int getRibbonNumber();

    void setRibbonNumber(int inputNumber);

private:
    BioBloomUnit* parentUnitAddress;

    int ribbonNumber;

};

#endif // UNITRIBBON_H
