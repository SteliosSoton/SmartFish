#ifndef MUSICWINDOW_H
#define MUSICWINDOW_H

#include <QWidget>
#include <QIcon>
#include <Qsize>

namespace Ui {class MusicWindow;}

class MusicWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MusicWindow(QWidget *parent = 0);
    ~MusicWindow();

public slots:
    void backButtonPressSlot();

private:
    Ui::MusicWindow *ui;

    void setupPushButtons();
    void setupPushButtonFunctions();
};

#endif // MUSICWINDOW_H
