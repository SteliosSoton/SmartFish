#include "graphdisplay.h"
#include "ui_graphdisplay.h"

graphDisplay::graphDisplay(QString graphType, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::graphDisplay)
{
    ui->setupUi(this);
    chart= new Chart(graphType);
    QChartView *graphView=new QChartView(chart, this);
    printf("chartview happned \n");
    //chart->setIdeal(28);
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


graphDisplay::graphDisplay(QString graphType, int ideal, QWidget *parent):
    QWidget(parent),
    ui(new Ui::graphDisplay)
{
    {
        ui->setupUi(this);
        chart= new Chart(graphType);
        QChartView *graphView=new QChartView(chart, this);
        printf("chartview happned \n");
        //chart->setIdeal(28);
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
    chart->setIdeal(ideal);
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

