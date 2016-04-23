#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "src/callnativegallery.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("CallNativeGallery", new CallNativeGallery(&engine));

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}

