#ifndef DATARIBBON_H
#define DATARIBBON_H

#include <QWidget>
#include <biobloomunit.h>

namespace Ui {class DataRibbon;}

class BioBloomUnit;
class DataRibbon : public QWidget
{
    Q_OBJECT

public:
    explicit DataRibbon(BioBloomUnit* inputParentUnit, QWidget *parent = 0);
    ~DataRibbon();

    void setDataTitle(QString newTitle);
    void changeDataNumber(QString newNumber);

    Ui::DataRibbon *ui;

private:
    BioBloomUnit* parentUnitAddress;
};

#endif // DATARIBBON_H
