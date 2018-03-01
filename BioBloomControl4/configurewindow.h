#ifndef CONFIGUREWINDOW_H
#define CONFIGUREWINDOW_H

#include <QWidget>
#include <QNetworkAccessManager>

#include "biobloomunit.h"
#include "plantprofile.h"

namespace Ui {class ConfigureWindow;}

class BioBloomUnit;
class ConfigureWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigureWindow(QString unitMacAddress, BioBloomUnit* inputParentUnit, QWidget *parent = 0);
    ~ConfigureWindow();

    QVector<PlantProfile*> plantProfile;


public slots:
    void applyButtonPressSlot(QString plantName, QString plantProfile);
    void plantTypeSelectionSlot(QString inputPlantType);

private:
    Ui::ConfigureWindow *ui;

    BioBloomUnit* parentUnitImage;

    QString unitMacAddress;
    QString newUnitName;
    QString newUnitType;
    PlantProfile* newPlantProfile;

    void setupComboBox();
    void setupPlantProfiles();
    void updateDatabase();

};

#endif // CONFIGUREWINDOW_H
