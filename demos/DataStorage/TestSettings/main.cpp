#include <QApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setOrganizationDomain("github/gdpurjyfs");
    app.setOrganizationName("gdpurjyfs");
    app.setApplicationName("TestSettings");
    app.setApplicationDisplayName("TestSettings");
    app.setApplicationVersion("0.0.1");

    QSettings extraSettings;
    extraSettings.beginGroup("CPP");
    extraSettings.setValue("cppSettings", "this is cpp settings");
    extraSettings.endGroup();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    // try to get settings that create in qml

    QSettings applicationWindowOption;
    // QVariant(int, 517)
    qDebug() << applicationWindowOption.value("ApplicationWindow/applicationWindowWidth");
    // "\\HKEY_CURRENT_USER\\Software\\gdpurjyfs\\TestSettings"
    qDebug() << applicationWindowOption.fileName();

    return app.exec();
}
