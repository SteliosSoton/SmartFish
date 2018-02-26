/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "chart.h"
#include <QtCharts>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>
#include <cmath>

Chart::Chart(QString desiredType)
   {
    graphType=desiredType;
    axisY = new QValueAxis;
    axisX = new QDateTimeAxis;
    printf("defined chart");

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
    axisX->setRange(QDateTime().currentDateTime(), QDateTime().currentDateTime().addSecs(10));
    QValueAxis *axisY = new QValueAxis;
    addAxis(axisY, Qt::AlignLeft);
    data_series->attachAxis(axisY);

    //axisY->setTickCount(11);
    printf("attached axes");
    printf("added series");
    idealSeries->attachAxis(axisX);
    idealSeries->attachAxis(axisY);
    //change title and y axis depending on the ata being displayed
    if(graphType=="temperature")
        {
            setTitle("Temperature Over Time");
            axisY->setTitleText("temperature/degrees");
            axisY->setRange(0, 100);

        }

}


void Chart::addPoint(qint64 dataNumber, int dataValue)//this adds a point to the chart. maybe datanumber should be ddatetime
{
    data_series->append(dataNumber, dataValue/10);


    printf("%d", data_series->pointsVector().first().x());
    idealSeries->append(axisX->min().toMSecsSinceEpoch(), idealValue);   //data_series->pointsVector().first().x(), idealValue);
    idealSeries->append(data_series->pointsVector().last().x(), idealValue);
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
        idealSeries->remove(idealSeries->pointsVector().first().x(), idealValue);
        idealSeries->append(axisX->min().toMSecsSinceEpoch(), idealValue);



    }
    else if(desiredstart=="a week ago")
    {
        axisX->setRange(QDateTime().currentDateTime().addDays(-7), QDateTime().currentDateTime());
        axisX->setTitleText("Date received");
        axisX->setFormat("ddd:hh:mm");
        axisX->setTickCount(3);
        idealSeries->remove(idealSeries->pointsVector().first().x(), idealValue);
        idealSeries->append(axisX->min().toMSecsSinceEpoch(), idealValue);



    }

    else if(desiredstart=="an hour ago")
    {
        axisX->setRange(QDateTime().currentDateTime().addSecs(-3600), QDateTime().currentDateTime());
        axisX->setTitleText("Time received");
        axisX->setFormat("ddd:hh:mm");
        axisX->setTickCount(5);
        idealSeries->remove(idealSeries->pointsVector().first().x(), idealValue);
        idealSeries->append(axisX->min().toMSecsSinceEpoch(), idealValue);
    }


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

