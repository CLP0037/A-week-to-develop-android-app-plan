#include <QApplication>
#include <QQmlApplicationEngine>
#include <qqml.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("DataStorage");
    app.setOrganizationName("GDPURJYFS");
    app.setOrganizationDomain("github.com/GDPURJYFS");
    app.setApplicationVersion("0.1.0");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/DataStorage/main.qml")));

    return app.exec();
}
