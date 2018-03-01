#ifndef DATARIBBON_H
#define DATARIBBON_H

#include <QWidget>

namespace Ui {class DataRibbon;}

class DataRibbon : public QWidget
{
    Q_OBJECT

public:
    explicit DataRibbon(QWidget *parent = 0);
    ~DataRibbon();

    void setDataTitle(QString newTitle);
    void changeDataNumber(QString newNumber);

    Ui::DataRibbon *ui;
};

#endif // DATARIBBON_H
