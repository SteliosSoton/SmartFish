#ifndef MUSICWINDOW_H
#define MUSICWINDOW_H

#include <QWidget>
#include <QIcon>
#include <Qsize>
#include <QNetworkAccessManager>

namespace Ui {class MusicWindow;}

class MusicWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MusicWindow(QString unitMacAddress, QWidget *parent = 0);               //ADD ALL SONGS TO LIST
    ~MusicWindow();                                                                 //CONNECT UP SONG BUTTON SIGNALS TO SLOTS
                                                                                   //ADD VOLUME CONTROL

public slots:
    void backButtonPressSlot();

private:
    Ui::MusicWindow *ui;

    void setupPushButtons();
    void setupPushButtonFunctions();
};

#endif // MUSICWINDOW_H
