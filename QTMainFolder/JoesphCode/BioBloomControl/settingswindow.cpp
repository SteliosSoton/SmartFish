#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent), ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);

    QPalette WindowPalette;
    WindowPalette.setColor(QPalette::Background, Qt::white);
    this->setPalette(WindowPalette);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}
