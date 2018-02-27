/*      Define Header File      */
#ifndef UNITWINDOW_H
#define UNITWINDOW_H

/*      Library Classes         */
#include <QWidget>
#include <QIcon>
#include <Qsize>

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
    explicit UnitWindow(QWidget *parent = 0);
    ~UnitWindow();

public slots:
    void backButtonPressSlot();
    void musicButtonPressSlot();
    void settingsButtonPressSlot();

    void plantNamePressSlot();

    void tempButtonPressSlot();
    void lightButtonPressSlot();
    void moitureButtonPressSlot();
    void humidityButtonPressSlot();

private:
    Ui::UnitWindow *ui;

    MusicWindow* musicWindowAddress;
    SettingsWindow* settingsWindowAddress;
    DataRibbon* tempRibbonAddress;
    DataRibbon* lightRibbonAddress;
    DataRibbon* moistureRibbonAddress;
    DataRibbon* humidityRibbonAddress;

    void setupOtherWindows();
    void setupDataDisplay();
    void setupPushButtonFunctions();

};

#endif // UNITWINDOW_H
