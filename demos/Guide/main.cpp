#include <QApplication>
#include <QQmlApplicationEngine>

#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
#endif//

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    app.setApplicationName("Guide");
    app.setOrganizationName("GDPURJYFS");
    app.setOrganizationDomain("github.com/GDPURJYFS");
    app.setApplicationVersion("0.1.2");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/Guide/main.qml")));

    return app.exec();
}
