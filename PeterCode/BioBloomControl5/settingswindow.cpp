#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(QString unitMacAddress, QWidget *parent) : QWidget(parent), ui(new Ui::SettingsWindow), unitMacAddress(unitMacAddress)
{
    ui->setupUi(this);

    QPalette WindowPalette;                                                                     //Create a palette
    WindowPalette.setColor(QPalette::Background, Qt::white);                                   //Configure the palette to fill the background with white
    this->setPalette(WindowPalette);                                                          //Set the palette

    setupPushButtons();
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}


void SettingsWindow::backButtonPressSlot()
{
    this->close();
}

void SettingsWindow::muteButtonPressSlot()
{

    QString ActionID = "mute";
    performAction(ActionID); //toggles mute on the speaker

}

void SettingsWindow::RGBControlButtonPressSlot()
{

        //HARD CODED MAC ADDRESS
        unitMacAddress = "2C:3A:E8:37:D8:6A";
        //HARD CODED RGB VALUES
        QString r = "1";
        QString g = "1";
        QString b = "0";
        //YELLOW


        qDebug()<< unitMacAddress;

        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        connect(manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(replyFinished(QNetworkReply*)));

        QUrl url;
        QByteArray postData;

        url.setUrl("http://192.168.5.1:80/rgb_request.php");
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

        QString postKey = "mac";
        QString postKey2 = "r";
        QString postKey3 = "g";
        QString postKey4 = "b";




        postData.append(postKey).append("=").append(unitMacAddress).append("&").append(postKey2).append("=").append(r).append("&").append(postKey3).append("=").append(g).append("&").append(postKey4).append("=").append(b).append("&");
        manager->post(request,postData);

}

void SettingsWindow::toggleLEDButtonPressSlot()
{
    QString ActionID = "leds";
    performAction(ActionID);  //turns on the leds
}

void SettingsWindow::toggleWaterButtonPressSlot()
{
    QString ActionID = "water";
    performAction(ActionID); //waters the plant
}

/*              Member Methods                  */
void SettingsWindow::setupPushButtons()
{
    connect(ui->BackButton, SIGNAL(released()), this, SLOT(backButtonPressSlot()));
    connect(ui->MuteButton, SIGNAL(released()), this, SLOT(muteButtonPressSlot()));
    connect(ui->RGBControlButton, SIGNAL(released()), this, SLOT(RGBControlButtonPressSlot()));
    connect(ui->ToggleLEDButton, SIGNAL(released()), this, SLOT(toggleLEDButtonPressSlot()));
    connect(ui->ToggleWaterButton, SIGNAL(released()), this, SLOT(toggleWaterButtonPressSlot()));

}

void SettingsWindow::performAction(QString actionID)
{
    //HARD CODED MAC ADDRESS
    unitMacAddress = "2C:3A:E8:37:D8:6A";


    qDebug()<< unitMacAddress;
    qDebug() << actionID;

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    QUrl url;
    QByteArray postData;

    url.setUrl("http://192.168.5.1:80/action_request.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QString postKey = "mac";
    QString postKey2 = "id";



    postData.append(postKey).append("=").append(unitMacAddress).append("&").append(postKey2).append("=").append(actionID).append("&");
    manager->post(request,postData);

    // the action 'ID' needs to be:
    // "water" to tell the pot to water the plant //this will be based on the humidity readings
    // "leds" to tell the pot to turn on the leds // this will be based on the light reading aswell as an enable and disable toggle switch?
    // "mute" to tell the pot to mute all sound effects // this can be from the state of a toggle switch?
    //more may follow when and /if we need the actions
}
void SettingsWindow:: finished(QNetworkReply*){}
void SettingsWindow:: replyFinished(QNetworkReply*){}

void SettingsWindow::dataRequestTestFunction()
{
    //HARD CODED MAC ADDRESS
    unitMacAddress = "2C:3A:E8:37:D8:6A";


    qDebug()<< unitMacAddress;

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    QUrl url;
    QByteArray postData;

    url.setUrl("http://192.168.5.1:80/data_request.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QString postKey = "mac";
    QString postKey2 = "id";



    postData.append(postKey).append("=").append(unitMacAddress).append("&");
    manager->post(request,postData);
}
