#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>

namespace Ui {class SettingsWindow;}

class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = 0);
    ~SettingsWindow();

public slots:
    void backButtonPressSlot();
    void muteButtonPressSlot();
    void RGBControlButtonPressSlot();
    void toggleLEDButtonPressSlot();
    void toggleWaterButtonPressSlot();

private:
    Ui::SettingsWindow *ui;

    /*              Member Methods                  */
    void setupPushButtons();
};

#endif // SETTINGSWINDOW_H
