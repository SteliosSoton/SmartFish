#ifndef QNETWORKMANAGER_MAC_H
#define QNETWORKMANAGER_MAC_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>

class QNetworkManager_mac : public QNetworkAccessManager
{
    Q_OBJECT

public:
    explicit QNetworkManager_mac(QNetworkAccessManager *parent = nullptr);

signals:


public slots:
};

#endif // QNETWORKMANAGER_MAC_H
