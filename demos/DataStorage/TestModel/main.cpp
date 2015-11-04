#include <QApplication>
#include <QQmlApplicationEngine>

#include <QtQml>
#include "testmodel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<TestModel>("Test", 1, 0, "TestModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
