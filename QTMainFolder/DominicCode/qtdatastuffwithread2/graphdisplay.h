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
    explicit graphDisplay(QString graphType, int ideal, QWidget *parent = 0);
    void extractData();
    ~graphDisplay();
    void addPoint(qint64 dataNumber, int dataValue);//int dataNumber
    void setIdeal(float ideal);

private:
    QComboBox *menu;
    Ui::graphDisplay *ui;
    Chart *chart;
    QString dataType;
};

#endif // GRAPHDISPLAY_H
