#ifndef GRAPHDISPLAY_H
#define GRAPHDISPLAY_H

#include <QWidget>

namespace Ui {
class graphDisplay;
}

class graphDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit graphDisplay(QWidget *parent = 0);
    ~graphDisplay();

private:
    Ui::graphDisplay *ui;
};

#endif // GRAPHDISPLAY_H
