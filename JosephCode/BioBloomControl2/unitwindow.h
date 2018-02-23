/*      Define Header File      */
#ifndef UNITWINDOW_H
#define UNITWINDOW_H

/*      Library Classes         */
#include <QWidget>
#include <QIcon>
#include <Qsize>

#include "musicwindow.h"

namespace Ui {class UnitWindow;}

/*          Class Declarations          */
class UnitWindow : public QWidget
{
    Q_OBJECT

public:
    explicit UnitWindow(QWidget *parent = 0);
    ~UnitWindow();

public slots:
    void backButtonPressSlot();
    void musicButtonPressSlot();

private:
    Ui::UnitWindow *ui;
    MusicWindow* musicWindowAddress;

    void setupPushButtons();
    void setupPushButtonFunctions();

};

#endif // UNITWINDOW_H
