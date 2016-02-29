#include <QApplication>
#include <QQmlApplicationEngine>

#include <QNetworkAccessManager>
#include <QNetworkDiskCache>
#include <QStandardPaths>
#include <QQmlNetworkAccessManagerFactory>

class MyNetworkAccessManagerFactory : public QQmlNetworkAccessManagerFactory
{
public:
    virtual QNetworkAccessManager *create(QObject *parent);
};

QNetworkAccessManager *MyNetworkAccessManagerFactory::create(QObject *parent)
{
    QNetworkAccessManager *nam = new QNetworkAccessManager(parent);
    QNetworkDiskCache* diskCache = new QNetworkDiskCache(nam);

    QString cachePath = QStandardPaths::displayName(QStandardPaths::CacheLocation);

    qDebug() << "cache path:" << cachePath;

    diskCache->setCacheDirectory(cachePath);
    diskCache->setMaximumCacheSize(100 * 1024 * 1024);   // 这里设置的缓存大小为 100 MB

    nam->setCache(diskCache);

    return nam;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //! [0]
    engine.setNetworkAccessManagerFactory(new MyNetworkAccessManagerFactory);
    //! [0]

    engine.load(QUrl(QStringLiteral("qrc:/qml/NetworkImageCache/main.qml")));

    return app.exec();
}

