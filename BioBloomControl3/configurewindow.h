#ifndef CONFIGUREWINDOW_H
#define CONFIGUREWINDOW_H

#include <QWidget>
#include <QNetworkAccessManager>

namespace Ui {class ConfigureWindow;}

class ConfigureWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigureWindow(QString unitMacAddress, QWidget *parent = 0);
    ~ConfigureWindow();

public slots:
    void applyButtonPressSlot(QString plantName, QString plantProfile);

private:
    Ui::ConfigureWindow *ui;

    QString unitMacAddress;

    void updateDatabase();
};

#endif // CONFIGUREWINDOW_H
