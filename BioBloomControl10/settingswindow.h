#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QDebug>
#include "biobloomunit.h"

namespace Ui {class SettingsWindow;}

class BioBloomUnit;
class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWindow(BioBloomUnit* inputParentUnit, QWidget *parent = 0);
    ~SettingsWindow();

    bool muteFlag;

public slots:
    void backButtonPressSlot();
    void muteButtonPressSlot();

    void redLEDButtonPressSlot();
    void greenLEDButtonPressSlot();
    void blueLEDButtonPressSlot();
    void magentaLEDButtonPressSlot();
    void cyanLEDButtonPressSlot();
    void yellowLEDButtonPressSlot();
    void whiteLEDButtonPressSlot();
    void toggleLEDButtonPressSlot();

    void manualWaterButtonPressSlot();
    void toggleWaterButtonPressSlot();


private:
    Ui::SettingsWindow *ui;

    BioBloomUnit* parentUnitAddress;


    /*              Member Methods                  */
    void setupPushButtons();
    void performAction(QString);
};

#endif // SETTINGSWINDOW_H
