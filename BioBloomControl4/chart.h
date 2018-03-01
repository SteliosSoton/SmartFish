#ifndef CHART_H
#define CHART_H

#include <QtCharts>

class Chart: public QChart
{
    Q_OBJECT

public:
    Chart(QString desiredType);
    ~Chart();

    void addPoint(QDateTime dataNumber, int dataValue);//int dataNumber
    void setIdeal(float ideal);
    void setYmax();
    void setYmin();

public slots:
    void rangeSignal(QString desiredstart);

private:
    QLineSeries *data_series;
    QLineSeries *idealSeries;
    QValueAxis *axisY;
    QDateTimeAxis *axisX;
    qint64 newTime;
    QString graphType;
    float newValue;
    float idealValue;
};

#endif /* CHART_H */
