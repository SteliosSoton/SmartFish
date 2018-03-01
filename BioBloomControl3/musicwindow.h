#ifndef MUSICWINDOW_H
#define MUSICWINDOW_H

#include <QWidget>
#include <QIcon>
#include <Qsize>
#include <QNetworkAccessManager>

namespace Ui {class MusicWindow;}

class MusicWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MusicWindow(QString unitMacAddress, QWidget *parent = 0);
    ~MusicWindow();

public slots:
    void backButtonPressSlot();

private:
    Ui::MusicWindow *ui;

    void setupPushButtons();
    void setupPushButtonFunctions();
};

#endif // MUSICWINDOW_H
