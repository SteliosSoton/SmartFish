#include "GraphDisplay.h"

GraphDisplay::GraphDisplay(QString graphType, QWidget *parent) : QWidget(parent)
{   //initialise members
    chart= new Chart(graphType);
    QChartView *graphView=new QChartView(chart, this);
    graphView->setRenderHint(QPainter::Antialiasing);
    resize(360, 450);//resize appropriately
    menu =new QComboBox(this);
    menu->setGeometry(0, 0, 450, 20);// set size as required
    graphView->setGeometry(0, 20, 420, 340);
    menu->addItem("please select");
    menu->addItem("an hour ago");
    menu->addItem("a day ago");
    menu->addItem("a week ago");
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);

    QObject::connect(menu,SIGNAL(currentIndexChanged(QString)),chart,SLOT(rangeSignal(QString)));
    menu->show();
    graphView->show();
    //data read intialise stuff
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    qDebug() <<"90";
    
       connect(manager, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(graphDataFetchFinished(QNetworkReply*)));

       QUrl url;
       QByteArray postData;
       url.setUrl("http://192.168.5.1:80/graph_data.php");
       QNetworkRequest request(url);
       request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
       
    qDebug() << macAddress;
    
       QString postKey = "mac";
       QString postValue = macAddress; //GET JOE TO PASS THE MAC ADDRESS ID FOR THE RIGHT PLANT TO HERE
                               // CAN GET HIM TO DO IT TOMORROW
    qDebug() << "91";
       postData.append(postKey).append("=").append(postValue).append("&");
       manager->post(request,postData);


}

GraphDisplay::GraphDisplay(QString graphType, int ideal, QString inputMacAddress, QWidget *parent): QWidget(parent)
{//initialise members with ideal vvalue

    chart= new Chart(graphType);
    QChartView *graphView=new QChartView(chart, this);
    graphView->setRenderHint(QPainter::Antialiasing);
    resize(350, 420);
    menu =new QComboBox(this);
    menu->setGeometry(0, 0, 420, 20);// maybe have this as a size policy
    graphView->setGeometry(0, 20, 420, 330);
    menu->addItem("please select");
    menu->addItem("an hour ago");
    menu->addItem("a day ago");
    menu->addItem("a week ago");
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);

    QObject::connect(menu,SIGNAL(currentIndexChanged(QString)),chart,SLOT(rangeSignal(QString)));
    menu->show();
    graphView->show();

    chart->setIdeal(ideal);
    //data read initialise stuff
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
       connect(manager, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(graphDataFetchFinished(QNetworkReply*)));

       QUrl url;
       QByteArray postData;
       url.setUrl("http://192.168.5.1:80/graph_data.php");
       QNetworkRequest request(url);
       request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

       QString postKey = "mac";
       QString postValue = inputMacAddress;
       qDebug() << "this dodad";
       qDebug() << inputMacAddress;

       postData.append(postKey).append("=").append(postValue).append("&");
       manager->post(request,postData);

}

GraphDisplay::GraphDisplay(QString graphType, int ideal, QWidget *parent): QWidget(parent)
{//initialise members with ideal vvalue

    chart= new Chart(graphType);
    QChartView *graphView=new QChartView(chart, this);
    graphView->setRenderHint(QPainter::Antialiasing);
    resize(350, 420);
    menu =new QComboBox(this);
    menu->setGeometry(0, 0, 420, 20);// maybe have this as a size policy
    graphView->setGeometry(0, 20, 420, 330);
    menu->addItem("please select");
    menu->addItem("an hour ago");
    menu->addItem("a day ago");
    menu->addItem("a week ago");
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);

    QObject::connect(menu,SIGNAL(currentIndexChanged(QString)),chart,SLOT(rangeSignal(QString)));
    menu->show();
    graphView->show();

    chart->setIdeal(ideal);
    //data read initialise stuff
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
       connect(manager, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(graphDataFetchFinished(QNetworkReply*)));

       QUrl url;
       QByteArray postData;
       url.setUrl("http://192.168.5.1:80/graph_data.php");
       QNetworkRequest request(url);
       request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

       QString postKey = "mac";
       QString postValue = macAddress; 
       postData.append(postKey).append("=").append(postValue).append("&");
       manager->post(request,postData);

}

GraphDisplay::~GraphDisplay()
{}

void GraphDisplay::addPoint(QDateTime dataNumber, int dataValue)// this addpoint needs to call the chart's addpoint
{
    chart->addPoint(dataNumber.toMSecsSinceEpoch(), dataValue);
}


void GraphDisplay::setIdeal(float ideal)// this setideal needs to call the chart's setideal
{
    chart->setIdeal(ideal);
}


//SLOT FOR DATA RETURNED FROM NETWORK REQUEST

void GraphDisplay:: graphDataFetchFinished(QNetworkReply* reply)
{
    reply->deleteLater();
    QByteArray data_reply = reply->readAll();
    QString dataString(data_reply);
   QStringList points_list = dataString.split( "," );
   QStringList points_div_ten;
   for(int i=0;i<points_list.count();i++)
   if(points_list[i].isEmpty())
   {
       points_list.takeAt(i);
   }
   for(int i=0;i<points_list.count();i++)
   {
        qDebug()<< points_list[i];
   }

   int i=0;
    if(chart->getGraphType()=="light")
    {
        i=0;
    }
    else if(chart->getGraphType()=="humidity")
    {
         i=1;
    }
    else if(chart->getGraphType()=="moisture")
    {
        i=2;
    }
    if(chart->getGraphType()=="temperature")
    {
        i=3;
    }
    while(i<points_list.count())
    {
        qDebug()<< points_list[i];
        qint64 timeOfValue=QDateTime().currentDateTime().toMSecsSinceEpoch()-(points_list.count()/6-i/6)*60000;//check my arithmetic, this should find the date/time the datapoint was recorded
        chart->addPoint(timeOfValue, ((points_list[i].toDouble())));
    i+=6;
    }


}

//POINTS_LIST IS THE QStringList
//could change this string to be a global variable in the class, whatever you need bro
//points_list[0], [6], [12] ... are light level
//points_list[1], [7], [13] ... are air humidity
//points_list[2], [8], [14] ... are soil moisture
//points_list[3], [9], [15] ... are temperature
//points_list[4], [unnamedMacAddresses], [16] ... are water level
//points_list[5], [11], [17] ... are battery level


void GraphDisplay::setMacAddress(QString inputMacAddress)
{
    macAddress = inputMacAddress;
}

