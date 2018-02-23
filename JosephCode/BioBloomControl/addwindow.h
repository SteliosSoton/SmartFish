#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QWidget>

namespace Ui {
class AddWindow;
}

class AddWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AddWindow(QWidget *parent = 0);
    ~AddWindow();

private:
    Ui::AddWindow *ui;
};

#endif // ADDWINDOW_H
