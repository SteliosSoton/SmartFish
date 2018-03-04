#include "chart.h"
#include <QtCharts>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>
#include <cmath>

Chart::Chart(QString desiredType)
   {
    idealValue=100000;// if the ideal value deoesn't change from this it won't be displayed
    graphType=desiredType;
    axisY = new QValueAxis;
    axisX = new QDateTimeAxis;

    data_series = new QLineSeries(this);
    idealSeries = new QLineSeries(this);
    addSeries(data_series);
    addSeries(idealSeries);
    axisY->setLabelFormat("%i");

    printf("defined series");
    QPen green(Qt::green);
    QPen red(Qt::red);
    green.setWidth(3);
    data_series->setPen(green);
    idealSeries->setPen(red);

    printf("appended first value");
    axisX->setTitleText("Time");
    addAxis(axisX, Qt::AlignBottom);
    data_series->attachAxis(axisX);
    axisX->setFormat("hh:mm:ss");
    axisX->setRange(QDateTime().currentDateTime(), QDateTime().currentDateTime().addSecs(10));//set default range
    QValueAxis *axisY = new QValueAxis;
    addAxis(axisY, Qt::AlignLeft);
    data_series->attachAxis(axisY);

    //axisY->setTickCount(11);
    idealSeries->attachAxis(axisX);
    idealSeries->attachAxis(axisY);
    //change title and y axis depending on the ata being displayed
    if(graphType=="temperature")
        {
            setTitle("Temperature Over Time");
            axisY->setTitleText("temperature/degrees celsius");
            axisY->setRange(0, 100);

        }

    else if(graphType=="light")
        {
            setTitle("Light level over Time");
            axisY->setTitleText("Light level/ %");
            axisY->setRange(0, 100);

        }
    else if(graphType=="moisture")
            {
                setTitle("Soil Moisture level over Time");
                axisY->setTitleText("Moisture level/ %");
                axisY->setRange(0, 100);

            }
    else if(graphType=="humidity")
            {
                setTitle("Air Humidity level over Time");
                axisY->setTitleText("Humidity / %");
                axisY->setRange(0, 100);

            }

}


void Chart::addPoint(qint64 dataNumber, int dataValue)//this adds a point to the chart
{
    data_series->append(dataNumber, dataValue/10);

    if(idealValue!=100000){
    idealSeries->append(axisX->min().toMSecsSinceEpoch(), idealValue);   //data_series->pointsVector().first().x(), idealValue);
    idealSeries->append(data_series->pointsVector().last().x(), idealValue);
    }
    axisX->setMax(QDateTime().currentDateTime());
    /*setYmax();
    printf("finishedYmax");
    setYmin();
    printf("finishedYmin");*/

}


Chart::~Chart()//destructor
{

}
void Chart::setIdeal(float ideal)
{
    idealValue=ideal;
}



void Chart::rangeSignal(QString desiredstart) //change the range being viewed appropriately
{
    if(desiredstart=="a day ago")
    {
        axisX->setRange(QDateTime().currentDateTime().addDays(-1), QDateTime().currentDateTime());
        axisX->setTitleText("Time received");
        axisX->setFormat("hh:mm");
        axisX->setTickCount(5);
        if(idealValue!=100000){
        idealSeries->remove(idealSeries->pointsVector().first().x(), idealValue);//remove useless points
        idealSeries->append(axisX->min().toMSecsSinceEpoch(), idealValue);
    }


    }
    else if(desiredstart=="a week ago")
    {
        axisX->setRange(QDateTime().currentDateTime().addDays(-7), QDateTime().currentDateTime());
        axisX->setTitleText("Date received");
        axisX->setFormat("ddd:hh:mm");
        axisX->setTickCount(3);
        if(idealValue!=100000){
        idealSeries->remove(idealSeries->pointsVector().first().x(), idealValue);//remove useless points
        idealSeries->append(axisX->min().toMSecsSinceEpoch(), idealValue);
        }


    }

    else if(desiredstart=="an hour ago")
    {
        axisX->setRange(QDateTime().currentDateTime().addSecs(-3600), QDateTime().currentDateTime());
        axisX->setTitleText("Time received");
        axisX->setFormat("ddd:hh:mm");
        axisX->setTickCount(5);
        if(idealValue!=100000){
        idealSeries->remove(idealSeries->pointsVector().first().x(), idealValue);//remove useless points
        idealSeries->append(axisX->min().toMSecsSinceEpoch(), idealValue);
        }
    }


}


QString Chart::getGraphType()
{
    return graphType;
}

/*void Chart::setYmax() //For Some Reason none of this works- the new values for
                        //Ymin and ymax are generated but the values refuse to be set to the axes
{

    int i =0;
    QVector<QPointF> pointsVector=data_series->pointsVector();
    int yMax=pointsVector.first().x();
    while(i<pointsVector.length())
    {
        if(pointsVector.value(i).x()>yMax)
            yMax=pointsVector.value(i).x();
        i++;
    }
    axisY->setMax(ceil(yMax/10)*10);
    printf("new ymax %i \n", yMax);


}


void Chart::setYmin()
{

    int i =0;

    QVector<QPointF> pointsVector=data_series->pointsVector();
    int yMin=pointsVector.first().x();

    while(i<pointsVector.length())
    {
        if(pointsVector.value(i).x()>yMin)
            yMin=pointsVector.value(i).x();
        i++;
    }
    axisY->setMin(floor(yMin/10)*10);
   // axisY->setMin(yMin);
    printf("new ymin %i \n", yMin);


}*/

