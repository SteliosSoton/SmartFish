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
    explicit ConfigureWindow(BioBloomUnit* inputParentUnit, QWidget *parent = 0);
    ~ConfigureWindow();

    Ui::ConfigureWindow *ui;

    QVector<PlantProfile*> plantProfile;

    QString unitMacAddress;
    QString newPlantName;
    PlantProfile* newPlantProfile;


public slots:
    void applyButtonPressSlot();                 //APPLY MUST ALSO WRITE TO SQL
    void plantTypeSelectionSlot(QString inputPlantType);
    void backButtonPressSlot();

private:                                                //POSSIBLE IMAGES - NOT HARD
    BioBloomUnit* parentUnitAddress;

    void setupComboBox();
    void setupPlantProfiles();
    void updateDatabase();

};

#endif // CONFIGUREWINDOW_H
