#include "graphdisplay.h"
#include "ui_graphdisplay.h"
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlTableModel>



graphDisplay::graphDisplay(QString graphType, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::graphDisplay)
{
    ui->setupUi(this);
    dataType=graphType;//might need if statement here, because this needs to be the same as the sql heading
    chart= new Chart(graphType);
    QChartView *graphView=new QChartView(chart, this);
    printf("chartview happned \n");
    chart->setIdeal(28);
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

}


graphDisplay::~graphDisplay()
{
    delete ui;
}

void graphDisplay::addPoint(QDateTime dataNumber, int dataValue)// this addpoint needs to call the chart's addpoint
{
    chart->addPoint(dataNumber, dataValue);
}


void graphDisplay::setIdeal(float ideal)// this setideal needs to call the chart's setideal
{
    chart->setIdeal(ideal);
}


void graphDisplay::extractData()
{
    QSqlDatabase *sensorDatabase= QSqlDatabase.addDatabase("QMYSQL");
    sensorDatabase.setDatabaseName("C:/Users/Dominic/Documents\D4/test_db-master/employees.sql");
    QSqlTableModel *model = new QSqlTableModel(this, sensorDatabase);
    model.setTable("employees");
    model.select();
    model->setHeaderData(0, Qt::Horizontal, tr("id"));//not sure if we need this
    model->setHeaderData(1, Qt::Horizontal, tr("mac"));//if we need them we need lots of them
    for(i=1;i<=model->rowCount();i++)
    {

       // this should calculate the time when the record was received in MsecsSinceEpoch. Assumes 1 reading/minute
       QDateTime timeOfValue=QDateTime().currentDateTime().toMSecsSinceEpoch()-(model->rowCount()-i)*60000;
       chart->addPoint(timeOfValue, model->record(i).value(dataType).toInt());
    }


    sensorDatabase->close();
    sensorDatabase->removeDatabase(QSqlDatabase.defaultConnection);
}

