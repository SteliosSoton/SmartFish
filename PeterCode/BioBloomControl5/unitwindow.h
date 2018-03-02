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
class UnitWindow : public QWidget
{
    Q_OBJECT

public:
    explicit UnitWindow(QString unitMacAddres, QWidget *parent = 0);                //PLANTNAME MUST BE WRITTEN BY THE UNITS CLASS
    ~UnitWindow();

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

    MusicWindow* musicWindowAddress;
    SettingsWindow* settingsWindowAddress;
    DataRibbon* tempRibbonAddress;
    DataRibbon* lightRibbonAddress;
    DataRibbon* moistureRibbonAddress;
    DataRibbon* humidityRibbonAddress;

    GraphDisplay* graphAddress;

    void setupOtherWindows(QString unitMacAddress);
    void setupDataDisplay();
    void setupPushButtonFunctions();

};

#endif // UNITWINDOW_H
