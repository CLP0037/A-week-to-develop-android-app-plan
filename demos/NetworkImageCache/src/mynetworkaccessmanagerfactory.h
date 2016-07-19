//! [参考](https://github.com/yeatse/pixiv-qt/blob/master/src/pnetworkaccessmanagerfactory.cpp#L19)

#ifndef MYNETWORKACCESSMANAGERFACTORY_H
#define MYNETWORKACCESSMANAGERFACTORY_H

#include <QQmlNetworkAccessManagerFactory>
#include <QNetworkAccessManager>

class MyNetworkAccessManagerFactory : public QQmlNetworkAccessManagerFactory
{
public:
    virtual QNetworkAccessManager *create(QObject *parent);
};

class MyNetworkAccessManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit MyNetworkAccessManager(QObject *parent=0);
protected:
    QNetworkReply *createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData);
};

#endif // MYNETWORKACCESSMANAGERFACTORY_H
