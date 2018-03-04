#include "unitribbon.h"
#include "ui_unitribbon.h"

UnitRibbon::UnitRibbon(BioBloomUnit *inputParentUnit, QWidget *parent) : QWidget(parent), ui(new Ui::UnitRibbon), parentUnitAddress(inputParentUnit)
{
    ui->setupUi(this);

}

UnitRibbon::~UnitRibbon()
{
    delete ui;
}

int UnitRibbon::getRibbonNumber()
{
    return ribbonNumber;
}

void UnitRibbon::setRibbonNumber(int inputNumber)
{
    ribbonNumber = inputNumber;
}

void UnitRibbon::updateData()
{
    qDebug() << "UnitRibbon::updateData()";

    qDebug() << parentUnitAddress->getPlantName();
    qDebug() << parentUnitAddress->unitPlantProfile->plantTypeName;

    ui->plantNameLabel->setText(parentUnitAddress->getPlantName());
    ui->plantTypeLabel->setText(parentUnitAddress->unitPlantProfile->plantTypeName);

    qDebug() << "Ribbon update complete";
}
