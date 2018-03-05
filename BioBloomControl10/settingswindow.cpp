#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(BioBloomUnit* inputParentUnit, QWidget *parent) : QWidget(parent), ui(new Ui::SettingsWindow), parentUnitAddress(inputParentUnit)
{
    ui->setupUi(this);

    muteFlag = 0;

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

    if(muteFlag == 0)
    {
        muteFlag = 1;

        QPixmap mutePixmap("muteButtonIcon");
        QIcon muteButtonIcon(mutePixmap);
        ui->MuteButton->setIcon(muteButtonIcon);
        ui->MuteButton->setIconSize(QSize(80,100));
    }

    else
    {
        muteFlag = 0;

        QPixmap unmutePixmap("UnmuteButtonIcon");
        QIcon unmuteButtonIcon(unmutePixmap);
        ui->MuteButton->setIcon(unmuteButtonIcon);
        ui->MuteButton->setIconSize(QSize(85,110));
    }

    QString ActionID = "mute";
    performAction(ActionID); //toggles mute on the speaker
}



void SettingsWindow::redLEDButtonPressSlot()
{
    //HARD CODED RGB VALUES
    QString r = "1";
    QString g = "0";
    QString b = "0";

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




    postData.append(postKey).append("=").append(parentUnitAddress->getMacAddress()).append("&").append(postKey2).append("=").append(r).append("&").append(postKey3).append("=").append(g).append("&").append(postKey4).append("=").append(b).append("&");
    manager->post(request,postData);
}

void SettingsWindow::greenLEDButtonPressSlot()
{
    //HARD CODED RGB VALUES
    QString r = "0";
    QString g = "1";
    QString b = "0";

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




    postData.append(postKey).append("=").append(parentUnitAddress->getMacAddress()).append("&").append(postKey2).append("=").append(r).append("&").append(postKey3).append("=").append(g).append("&").append(postKey4).append("=").append(b).append("&");
    manager->post(request,postData);
}

void SettingsWindow::blueLEDButtonPressSlot()
{
    //HARD CODED RGB VALUES
    QString r = "0";
    QString g = "0";
    QString b = "1";

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




    postData.append(postKey).append("=").append(parentUnitAddress->getMacAddress()).append("&").append(postKey2).append("=").append(r).append("&").append(postKey3).append("=").append(g).append("&").append(postKey4).append("=").append(b).append("&");
    manager->post(request,postData);
}

void SettingsWindow::magentaLEDButtonPressSlot()
{
    //HARD CODED RGB VALUES
    QString r = "1";
    QString g = "0";
    QString b = "1";

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




    postData.append(postKey).append("=").append(parentUnitAddress->getMacAddress()).append("&").append(postKey2).append("=").append(r).append("&").append(postKey3).append("=").append(g).append("&").append(postKey4).append("=").append(b).append("&");
    manager->post(request,postData);
}

void SettingsWindow::cyanLEDButtonPressSlot()
{
    //HARD CODED RGB VALUES
    QString r = "0";
    QString g = "1";
    QString b = "1";

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




    postData.append(postKey).append("=").append(parentUnitAddress->getMacAddress()).append("&").append(postKey2).append("=").append(r).append("&").append(postKey3).append("=").append(g).append("&").append(postKey4).append("=").append(b).append("&");
    manager->post(request,postData);
}

void SettingsWindow::yellowLEDButtonPressSlot()
{
    //HARD CODED RGB VALUES
    QString r = "1";
    QString g = "1";
    QString b = "0";

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




    postData.append(postKey).append("=").append(parentUnitAddress->getMacAddress()).append("&").append(postKey2).append("=").append(r).append("&").append(postKey3).append("=").append(g).append("&").append(postKey4).append("=").append(b).append("&");
    manager->post(request,postData);
}

void SettingsWindow::whiteLEDButtonPressSlot()
{
    //HARD CODED RGB VALUES
    QString r = "1";
    QString g = "1";
    QString b = "1";

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




    postData.append(postKey).append("=").append(parentUnitAddress->getMacAddress()).append("&").append(postKey2).append("=").append(r).append("&").append(postKey3).append("=").append(g).append("&").append(postKey4).append("=").append(b).append("&");
    manager->post(request,postData);
}

void SettingsWindow::toggleLEDButtonPressSlot()
{
    QString ActionID = "leds";
    performAction(ActionID);  //turns on the leds
}




void SettingsWindow::manualWaterButtonPressSlot()
{
    QString ActionID = "water";
    performAction(ActionID); //waters the plant
}

void SettingsWindow::toggleWaterButtonPressSlot()
{
    parentUnitAddress->disablePumpFlag = 1;
}



/*              Class Methods                 */
void SettingsWindow::setupPushButtons()
{
    connect(ui->BackButton, SIGNAL(released()), this, SLOT(backButtonPressSlot()));
    connect(ui->MuteButton, SIGNAL(released()), this, SLOT(muteButtonPressSlot()));

    connect(ui->RedLEDButton, SIGNAL(released()), this, SLOT(redLEDButtonPressSlot()));
    connect(ui->GreenLEDButton, SIGNAL(released()), this, SLOT(greenLEDButtonPressSlot()));
    connect(ui->BlueLEDButton, SIGNAL(released()), this, SLOT(blueLEDButtonPressSlot()));
    connect(ui->MagentaLEDButton, SIGNAL(released()), this, SLOT(magentaLEDButtonPressSlot()));
    connect(ui->CyanLEDButton, SIGNAL(released()), this, SLOT(cyanLEDButtonPressSlot()));
    connect(ui->YellowLEDButton, SIGNAL(released()), this, SLOT(yellowLEDButtonPressSlot()));
    connect(ui->WhiteLEDButton, SIGNAL(released()), this, SLOT(whiteLEDButtonPressSlot()));
    connect(ui->ToggleLEDButton, SIGNAL(released()), this, SLOT(toggleLEDButtonPressSlot()));

    connect(ui->ManualWaterButton, SIGNAL(released()), this, SLOT(manualWaterButtonPressSlot()));
    connect(ui->ToggleWaterButton, SIGNAL(released()), this, SLOT(toggleWaterButtonPressSlot()));

}

void SettingsWindow::performAction(QString actionID)
{
    //qDebug()<< parentUnitAddress->getMacAddress();
    //qDebug() << actionID;

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



    postData.append(postKey).append("=").append(parentUnitAddress->getMacAddress()).append("&").append(postKey2).append("=").append(actionID).append("&");
    manager->post(request,postData);

    // the action 'ID' needs to be:
    // "water" to tell the pot to water the plant //this will be based on the humidity readings
    // "leds" to tell the pot to turn on the leds // this will be based on the light reading aswell as an enable and disable toggle switch?
    // "mute" to tell the pot to mute all sound effects // this can be from the state of a toggle switch?
    //more may follow when and /if we need the actions
}
/*
void SettingsWindow:: finished(QNetworkReply*){}
void SettingsWindow:: replyFinished(QNetworkReply*){}

void SettingsWindow::dataRequestTestFunction()
{
    qDebug()<< parentUnitAddress->getMacAddress();

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



    postData.append(postKey).append("=").append(parentUnitAddress->getMacAddress()).append("&");
    manager->post(request,postData);
}
*/
