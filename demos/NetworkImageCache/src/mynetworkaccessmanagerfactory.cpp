#include "mynetworkaccessmanagerfactory.h"

#include <QNetworkDiskCache>
#include <QStandardPaths>
#include <QtDebug>

QNetworkAccessManager *MyNetworkAccessManagerFactory::create(QObject *parent)
{
    QNetworkAccessManager *nam = new MyNetworkAccessManager(parent);
    QNetworkDiskCache* diskCache = new QNetworkDiskCache(nam);

    QString cachePath = QStandardPaths::displayName(QStandardPaths::CacheLocation);

    qDebug() << "cache path:" << cachePath;

    diskCache->setCacheDirectory(cachePath);
    diskCache->setMaximumCacheSize(100 * 1024 * 1024);   // 这里设置的缓存大小为 100 MB

    nam->setCache(diskCache);

    return nam;
}


MyNetworkAccessManager::MyNetworkAccessManager(QObject *parent) :
    QNetworkAccessManager(parent)
{
}

QNetworkReply *MyNetworkAccessManager::createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData)
{

    /*
      Cookie: appver=1.5.0.75771;
      Referer: http://music.163.com/
    */
    /*
    QNetworkRequest req(request);
    if(req.url().toString().contains(".163.")) {
        if (!req.hasRawHeader("Referer")){
            req.setRawHeader("Referer", "http://music.163.com/");
        }
        req.setHeader(QNetworkRequest::CookieHeader, "ppver=1.5.0.75771;");
    }


    QNetworkReply *reply = this->QNetworkAccessManager::createRequest(op, req, outgoingData);
    return reply;
    */

    return this->QNetworkAccessManager::createRequest(op, request, outgoingData);
}
