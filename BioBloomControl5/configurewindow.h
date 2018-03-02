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

    QString unitMacAddress;
    QString newUnitName;
    QString newUnitType;
    PlantProfile* newPlantProfile;


public slots:
    void applyButtonPressSlot(QString plantName, QString plantProfile);                 //APPLY MUST ALSO WRITE TO SQL
    void plantTypeSelectionSlot(QString inputPlantType);

private:                                                //POSSIBLE IMAGES - NOT HARD
    Ui::ConfigureWindow *ui;

    BioBloomUnit* parentUnitImage;

    void setupComboBox();
    void setupPlantProfiles();
    void updateDatabase();

};

#endif // CONFIGUREWINDOW_H
