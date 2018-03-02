#include "musicwindow.h"
#include "ui_musicwindow.h"

MusicWindow::MusicWindow(QString unitMacAddress, QWidget *parent) : QWidget(parent), ui(new Ui::MusicWindow)
{
    ui->setupUi(this);

    QPalette WindowPalette;                                                                 //Create a palette
    WindowPalette.setColor(QPalette::Background, Qt::white);                               //Configure the palette to fill the background with white
    this->setPalette(WindowPalette);                                                      //Set the palette

    setupPushButtonFunctions();

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    QUrl url;
    QByteArray postData;

    url.setUrl("http://192.168.5.1:80/audio_request.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QString postKey = "mac";
    QString postValue = unitMacAddress;
    QString postKey2 = "volume";
    QString postValue2 = "insert volume here";
    QString postKey3 = "track";
    QString postValue3 = "insert track here";

    postData.append(postKey).append("=").append(postValue).append("&").append(postKey2).append("=").append(postValue2).append("&").append(postKey3).append("=").append(postValue3).append("&");
    manager->post(request,postData);

    //1 for first track
    //2 for second track etc.
    // will agree on a system so we know exactly what files correspond to each number
    //params.addQueryItem("volume_id", "...");
    //number between 0 and 30 //0 being mute
    //this could be based from a volume slider?
    //would also need volume change added as an action if the volume is altered during a sound effect?
    //depends how long the effects are?

}

MusicWindow::~MusicWindow()
{
    delete ui;
}

void MusicWindow::backButtonPressSlot()
{
    this->close();
}

void MusicWindow::setupPushButtons()
{
    
}

void MusicWindow::setupPushButtonFunctions()
{
   connect(ui->BackButton, SIGNAL(released()), this, SLOT(backButtonPressSlot()) );
}
