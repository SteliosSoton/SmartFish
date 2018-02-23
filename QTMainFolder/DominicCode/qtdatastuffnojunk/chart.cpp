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
    axisY->setRange(0, 100);
    axisY->setTickCount(11);
    printf("attached axes");
    printf("added series");
    idealSeries->attachAxis(axisX);
    idealSeries->attachAxis(axisY);

    if(graphType=="temperature")
        {
            axisY->setTitleText("temperature/degrees");
        }

}

/*void Chart::readDataBase()
{
    int i=0;
    while (i<10) {
        printf("in while loop\n");
        Sleep(500);
        data_series->append(QDateTime().currentDateTime().toMSecsSinceEpoch(), rand()%100);
        printf("appened value \n");
        i++;
    }
    idealTemp=30;
}*/

void Chart::addPoint(QDateTime dataNumber, int dataValue)
{
    data_series->append(dataNumber.toMSecsSinceEpoch(), dataValue/10);

    printf("%d", data_series->pointsVector().first().x());
    idealSeries->append(data_series->pointsVector().first().x(), idealValue);
    printf("appended first ideal");
    idealSeries->append(data_series->pointsVector().last().x(), idealValue);
    printf("appended last ideal");
    axisX->setMax(QDateTime().currentDateTime());
}

/*void Chart::setGraphType(QString desiredType){//This is a redundant test function
    graphType=desiredType;
    if(graphType=="temperature")
        {
            printf("WHAET THE FOOK %s %s ", graphType, desiredType);
            axisY->setRange(0, 80);
            axisY->setTitleText("temperature/degrees");
            axisY->setTitleVisible(true);
        }
    //TODO: set range according to graph type,get it to set range based on largest y value.
}*/


void Chart::setIdeal(float ideal)
{
    idealValue=ideal;
}



void Chart::rangeSignal(int desiredstart)
{
    printf("received signal %d \n", desiredstart);
    if(desiredstart==0)
    {
        axisX->setRange(QDateTime().currentDateTime().addDays(-1), QDateTime().currentDateTime());

    }
    else if(desiredstart==1)
    {
        axisX->setRange(QDateTime().currentDateTime().addDays(-1), QDateTime().currentDateTime());
        axisX->setTitleText("Time received");
        axisX->setFormat("hh:mm");
        axisX->setTickCount(13);


    }
    if(desiredstart==2)
    {
        axisX->setRange(QDateTime().currentDateTime().addDays(-7), QDateTime().currentDateTime());
        axisX->setTitleText("Date received");
        axisX->setFormat("ddd:hh:mm");
        axisX->setTickCount(8);


    }


}
