#ifndef GRAPHDISPLAY_H
#define GRAPHDISPLAY_H

#include <QWidget>
#include <QComboBox>
#include "chart.h"

namespace Ui {
class graphDisplay;
}

class graphDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit graphDisplay(QString graphType, QWidget *parent = 0);
    ~graphDisplay();
    void addPoint(QDateTime dataNumber, int dataValue);//int dataNumber
    void setIdeal(float ideal);

private:
    QComboBox *menu;
    Ui::graphDisplay *ui;
    Chart *chart;
};

#endif // GRAPHDISPLAY_H
