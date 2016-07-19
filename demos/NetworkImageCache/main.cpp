#include <QApplication>
#include <QQmlApplicationEngine>

#include "src/mynetworkaccessmanagerfactory.h"

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

