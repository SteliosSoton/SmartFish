#ifndef UNITWORKER_H
#define UNITWORKER_H

#include <QObject>
#include <QtNetwork\QNetworkAccessManager>

class UnitWorker : public QObject
{
    Q_OBJECT

public:
    explicit UnitWorker(QNetworkAccessManager* Manager, QString macAddress, QObject *parent = nullptr);
    ~UnitWorker;

signals:
    finishedSignal();

public slots:

};

#endif // UNITWORKER_H
