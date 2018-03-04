#ifndef MUSICWINDOW_H
#define MUSICWINDOW_H

#include <QWidget>
#include <QIcon>
#include <Qsize>
#include <QNetworkAccessManager>
#include "biobloomunit.h"

namespace Ui {class MusicWindow;}

class BioBloomUnit;
class MusicWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MusicWindow(BioBloomUnit* inputParentUnit, QWidget *parent = 0);        //ADD ALL SONGS TO LIST
    ~MusicWindow();                                                                 //CONNECT UP SONG BUTTON SIGNALS TO SLOTS
                                                                                   //ADD VOLUME CONTROL

    int volume;
    QString volumeString;
    bool pauseFlag;


public slots:
    void backButtonPressSlot();

    void volumeUpButtonPressSlot();
    void volumeDownButtonPressSlot();

    void pauseButtonPressSlot();

    void Track1ButtonPressSlot();
    void Track2ButtonPressSlot();
    void Track3ButtonPressSlot();
    void Track4ButtonPressSlot();
    void Track5ButtonPressSlot();
    void Track6ButtonPressSlot();
    void Track7ButtonPressSlot();
    void Track8ButtonPressSlot();
    void Track9ButtonPressSlot();
    void Track10ButtonPressSlot();
    void Track11ButtonPressSlot();
    void Track12ButtonPressSlot();
    void Track13ButtonPressSlot();
    void Track14ButtonPressSlot();

private:
    Ui::MusicWindow *ui;
    BioBloomUnit* parentUnitAddress;

    QVector<QPushButton*> songButtonAddress;
    QVector<QListWidgetItem*> songItemAddress;

    void setupPushButtons();
    void setupSongList();
    void setupPushButtonFunctions();
    void performAudioRequest(QString trackNumber);
};

#endif // MUSICWINDOW_H
