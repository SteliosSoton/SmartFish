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
#include "rangeselectmenu.h"
#include <conio.h>
#include "displaychart.h"

#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

QT_CHARTS_USE_NAMESPACE

QDateTime startTime;
QDateTime convertIndextoTime(int index)
{

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;
    displayChart chartview;
    printf("started");
    printf("main declared chart");
    /*Chart *chart = new Chart("temperature");
    chart->setTitle("Chart");
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);*/
    printf("animated \n");

    //QChartView chartView(chart);
    printf("chartview happned \n");
    //chart->setIdeal(28);

    //chartView.setRenderHint(QPainter::Antialiasing);
    window.setCentralWidget(&chartview);
    window.resize(820, 600);
   /* rangeSelectMenu *menu =new rangeSelectMenu;
    QObject::connect(menu,SIGNAL(currentIndexChanged(int)),chart,SLOT(rangeSignal(int)));
    //window.setMenuWidget(menu);
    //menu->setGeometry(10, 10, 10, 10);
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
    }*/

    window.show();
    return a.exec();
}
