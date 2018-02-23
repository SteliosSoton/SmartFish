#ifndef RANGESELECTMENU_H
#define RANGESELECTMENU_H

#include <QWidget>
#include <qcombobox.h>

namespace Ui {
class rangeSelectMenu;
}

class rangeSelectMenu : public QComboBox
{
    Q_OBJECT

public:
    explicit rangeSelectMenu(QComboBox *parent = 0);
    ~rangeSelectMenu();

private:
    Ui::rangeSelectMenu *ui;
};

#endif // RANGESELECTMENU_H
