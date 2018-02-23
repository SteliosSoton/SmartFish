#include "rangeselectmenu.h"
#include "ui_rangeselectmenu.h"

rangeSelectMenu::rangeSelectMenu(QComboBox *parent) :
    QComboBox(parent),
    ui(new Ui::rangeSelectMenu)
{
    ui->setupUi(this);
    addItem("please select");
    addItem("a day ago");
    addItem("a week ago");
}

rangeSelectMenu::~rangeSelectMenu()
{
    delete ui;
}
