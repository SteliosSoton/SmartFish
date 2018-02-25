#ifndef DISPLAYCHART_H
#define DISPLAYCHART_H

#include <QWidget>

namespace Ui {
class displayChart;
}

class displayChart : public QWidget
{
    Q_OBJECT
public:
    explicit displayChart(QWidget *parent = nullptr);
    ~displayChart();

private:
    Ui::displayChart *ui;

};

#endif // DISPLAYCHART_H


