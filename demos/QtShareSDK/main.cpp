#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "src/sharesdk.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterSingletonType<ShareSDK>("Share", 1, 0, "ShareSDK", ShareSDK::singletonProvider);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}

