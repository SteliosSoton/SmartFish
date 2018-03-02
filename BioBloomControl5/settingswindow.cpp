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

  performAction("mute");

}

void SettingsWindow::RGBControlButtonPressSlot()
{

}

void SettingsWindow::toggleLEDButtonPressSlot()
{
    performAction("leds"); //turns on the leds
}

void SettingsWindow::toggleWaterButtonPressSlot()
{
    performAction("water"); //waters the plant
}

/*              Member Methods                  */
void SettingsWindow::setupPushButtons()
{
    connect(ui->BackButton, SIGNAL(released()), this, SLOT(backButtonPressSlot()));
}

void SettingsWindow::performAction(QString actionID)
{
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
