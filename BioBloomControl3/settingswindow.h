#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include <QtNetwork/QNetworkAccessManager>

namespace Ui {class SettingsWindow;}

class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWindow(QString unitMacAddress, QWidget *parent = 0);
    ~SettingsWindow();

public slots:
    void backButtonPressSlot();
    void muteButtonPressSlot();
    void RGBControlButtonPressSlot();
    void toggleLEDButtonPressSlot();
    void toggleWaterButtonPressSlot();

private:
    Ui::SettingsWindow *ui;

    QString unitMacAddress;


    /*              Member Methods                  */
    void setupPushButtons();
    void performAction(QString);
};

#endif // SETTINGSWINDOW_H
