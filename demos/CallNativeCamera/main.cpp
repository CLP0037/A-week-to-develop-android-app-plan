#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "src/callnativecamera.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("CallNativeCamera", new CallNativeCamera(&engine));

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}

