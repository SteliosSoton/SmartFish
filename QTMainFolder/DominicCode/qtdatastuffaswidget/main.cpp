

#include "chart.h"
#include "graphdisplay.h"
#include <conio.h>

#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;
    printf("started");
    graphDisplay *graphView=new graphDisplay("temperature", 28);//the graphview constructor needs to be told what type of graph to display.
    window.setCentralWidget(graphView);
    graphView->show();
    window.resize(420, 350);

    int i=0;
    while (i<10) {//create test values over 5seconds
        printf("in while loop\n");
        Sleep(500);
        graphView->addPoint(QDateTime().currentDateTime(), (rand()%1000));
        printf("appended value \n");

        i++;
    }



    window.show();
    return a.exec();
}
