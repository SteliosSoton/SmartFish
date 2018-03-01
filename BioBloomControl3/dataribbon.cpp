/*                  Header File                    */
#include "dataribbon.h"
#include "ui_dataribbon.h"

/*           Constructor and Destructor            */
DataRibbon::DataRibbon(QWidget *parent) : QWidget(parent), ui(new Ui::DataRibbon)
{
    ui->setupUi(this);
}

DataRibbon::~DataRibbon()
{
    delete ui;
}

/*                Class Methods                   */
void DataRibbon::setDataTitle(QString newTitle)
{
    ui->dataTitle->setText(newTitle);
}

void DataRibbon::changeDataNumber(QString newNumber)
{
    ui->dataNumber->setText(newNumber);
}
