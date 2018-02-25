#include "displaychart.h"
#include "chart.h"
#include "rangeselectmenu.h"

displayChart::displayChart(QWidget *parent) : QWidget(parent)
{


    Chart *chart = new Chart("temperature");
    printf("animated \n");

    QChartView chartView(chart);

    printf("chartview happned \n");
    chart->setIdeal(28);

    chartView.setRenderHint(QPainter::Antialiasing);
    resize(350, 420);
    rangeSelectMenu *menu =new rangeSelectMenu;
    QObject::connect(menu,SIGNAL(currentIndexChanged(int)),chart,SLOT(rangeSignal(int)));
    //window.setMenuWidget(menu);
    menu->setGeometry(0, 0, 350, 20);
    chartView.setGeometry(0, 20, 350, 400);

    //chart->setGraphType("temperature");
    {
        int i=0;
        while (i<10) {
            printf("in while loop\n");
            Sleep(500);
            printf("appened value \n");
            chart->addPoint(QDateTime().currentDateTime(), (rand()%1000));
            i++;
        }
    }

}


displayChart::~displayChart();
{
    delete ui;
}
