#include "configurewindow.h"
#include "ui_configurewindow.h"

ConfigureWindow::ConfigureWindow(QString unitMacAddress, QWidget *parent) : QWidget(parent), ui(new Ui::ConfigureWindow), unitMacAddress(unitMacAddress)
{
    ui->setupUi(this);
}

ConfigureWindow::~ConfigureWindow()
{
    delete ui;
}

void ConfigureWindow::applyButtonPressSlot(QString plantName, QString plantProfile)
{

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    QUrl url;
    QByteArray postData;

    url.setUrl("http://192.168.5.1:80/personalise_plant.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QString postKey = "mac";
    QString postValue = unitMacAddress;
    QString postKey2 = "name";
    QString postValue2 = plantName;
    QString postKey3 = "profile";
    QString postValue3 = plantProfile;

    postData.append(postKey).append("=").append(postValue).append("&").append(postKey2).append("=").append(postValue2).append("&").append(postKey3).append("=").append(postValue3).append("&");
    manager->post(request,postData);

}
