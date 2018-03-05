/*      Define Header File      */
#ifndef UNITWINDOW_H
#define UNITWINDOW_H

/*      Library Classes         */
#include <QWidget>
#include <QIcon>
#include <Qsize>

#include "chart.h"
#include "graphdisplay.h"
#include "musicwindow.h"
#include "settingswindow.h"
#include "dataribbon.h"

namespace Ui {class UnitWindow;}

/*          Class Declarations          */
class MusicWindow;
class SettingsWindow;
class DataRibbon;
class UnitWindow : public QWidget
{
    Q_OBJECT

public:
    explicit UnitWindow(BioBloomUnit* inputParentUnit, QWidget *parent = 0);                //PLANTNAME MUST BE WRITTEN BY THE UNITS CLASS
    ~UnitWindow();

    void updateData();

public slots:
    void backButtonPressSlot();
    void musicButtonPressSlot();
    void settingsButtonPressSlot();

    void tempRibbonPressSlot();
    void lightRibbonPressSlot();
    void moistureRibbonPressSlot();
    void humidityRibbonPressSlot();

private:
    Ui::UnitWindow *ui;
    BioBloomUnit* parentUnitAddress;

    MusicWindow* musicWindowAddress;
    SettingsWindow* settingsWindowAddress;
    DataRibbon* tempRibbonAddress;
    DataRibbon* lightRibbonAddress;
    DataRibbon* moistureRibbonAddress;
    DataRibbon* humidityRibbonAddress;

    GraphDisplay* graphAddress;

    void setupOtherWindows();
    void setupDataDisplay();
    void setupPushButtonFunctions();

};

#endif // UNITWINDOW_H
