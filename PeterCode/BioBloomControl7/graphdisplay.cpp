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
}

GraphDisplay::~GraphDisplay()
{}

void GraphDisplay::addPoint(QDateTime dataNumber, int dataValue)// this addpoint needs to call the chart's addpoint
{
    chart->addPoint(dataNumber, dataValue);
}


void GraphDisplay::setIdeal(float ideal)// this setideal needs to call the chart's setideal
{
    chart->setIdeal(ideal);
}

