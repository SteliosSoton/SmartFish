#include "graphdisplay.h"
#include "ui_graphdisplay.h"
#include "chart.h"

graphDisplay::graphDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::graphDisplay)
{
    ui->setupUi(this);
    Chart *chart = new Chart("temperature");
    printf("animated \n");

    QChartView *graphView=new QChartView(chart, this);

    printf("chartview happned \n");
    chart->setIdeal(28);

    graphView->setRenderHint(QPainter::Antialiasing);
    resize(350, 420);
    QComboBox *menu =new QComboBox(this);
    menu->setGeometry(0, 0, 420, 20);
    graphView->setGeometry(0, 20, 420, 330);
    menu->addItem("please select");
    menu->addItem("a day ago");
    menu->addItem("a week ago");
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);

    QObject::connect(menu,SIGNAL(currentIndexChanged(int)),chart,SLOT(rangeSignal(int)));
    menu->show();
    graphView->show();
    //window.setMenuWidget(menu);

    //chart->setGraphType("temperature");

        int i=0;
        while (i<10) {
            printf("in while loop\n");
            Sleep(500);
            printf("appened value \n");
            chart->addPoint(QDateTime().currentDateTime(), (rand()%1000));
            i++;
        }
}


graphDisplay::~graphDisplay()
{
    delete ui;
}
