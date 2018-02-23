#include "unitribbon.h"
#include "ui_unitribbon.h"

UnitRibbon::UnitRibbon(QWidget *parent) : QWidget(parent), ui(new Ui::UnitRibbon)
{
    ui->setupUi(this);
}

UnitRibbon::~UnitRibbon()
{
    delete ui;
}
