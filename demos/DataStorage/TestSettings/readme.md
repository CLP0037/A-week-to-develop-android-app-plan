# 设置

保存设置是一款应用应该具备的功能。这里先介绍 `QML` 接口。

## Settings

```
import QtQuick.Window 2.1
import Qt.labs.settings 1.0

Window {
    id: window

    width: 800
    height: 600

    Settings {
        property alias x: window.x
        property alias y: window.y
        property alias width: window.width
        property alias height: window.height
    }
}
```

> 注意，`Qt.labs.settings` 模块可能在后期被移除。

上诉代码可以轻而易举的保存窗体的大小，并在下次启动时恢复窗体关闭时的大小。

通过设置 `Settings::category` 做到分组的效果。

## QSettings

> `C++` 中有 `QSettings`，`QSettings` 类提供“持久性”，平台独立的应用程序设置。意思是，程序关闭后 `QSettings` 把窗体大小，位置，用户设置的选项保存起来，下次打开程序时再重新加载。

> 如果你需要的是“非持久性” 基于内存的数据结构，可以考虑使用 `QMap<QString,QVariant>` 代替。

> 通常，对于Windows，配置信息保存在注册表中，Mac OS 是 `XML` 文件，`Unix` 是 `INI` 文件

具体用法和介绍可以查看如下文章：

[QSettings 用法（一）](http://blog.csdn.net/styyzxjq2009/article/details/8193594)

[Qt下QSettings类详解](http://yiluohuanghun.blog.51cto.com/3407300/952807)

不过需要注意的是，**不管是使用 `QML` 的 `Settings`，或者是`QSettings`，都需要设置一些应用的信息，例如应用名称，公司名称，域名，版本号等。另外，`Settings` 是基于 `QSettings` 而设计的， C++ 层面可以直接读取到 `QML` 的 `Settings`。**

```
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
```

```
import QtQuick 2.4
import QtQuick.Controls 1.3
import Qt.labs.settings 1.0

ApplicationWindow {
    id: window
    title: qsTr("Test Settings")
    width: 640
    height: 480
    visible: true

    Settings {
        id: applicationWindowOption
        category: "ApplicationWindow"
        property alias applicationWindowWidth : window.width
        property alias applicationWindowHeight : window.height
    }

    Settings {
        id: tryToGetCPPSettings
        category: "CPP"
        property string cppSettings
    }

    Component.onCompleted: {
        try {
            // qml: tryToGetCPPSettings.cppSettings:  this is cpp settings
            console.log("tryToGetCPPSettings.cppSettings: ",
                        tryToGetCPPSettings.cppSettings);
        }catch(e){  console.log(e); }
    }
}
```

从上述代码可以看出，一个设置在一个应用中是全局唯一的，使用前缀以及名称进行区别。

`QSettings::group` 对应到 `Settings::category`，`QSettings::setValue` 中的 `name` 参数对应到 `Settings` 中的属性。从上述代码可以看出，一个设置在一个应用中是全局唯一的，使用前缀以及名称进行区别。

`QSettings::group` 对应到 `Settings::category`，`QSettings::setValue` 中的 `name` 参数对应到 `Settings` 中的属性。