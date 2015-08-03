# 引导页 

引导页的作用大体如下：

1. 介绍应用或者介绍新特性

2. 比 **SplashScreen** 更多的信息

3. 进行交互式引导

特点是：

在应用某个版本第一次启动时显示，下次启动不显示。在应用进行更新或者降级后，仍然会进行展示。

这里只提供使用  QML 的实现方式，其他实现方式可自行搜索。

## 记录应用启动次数

`Settings` 类似于 **C++** `QSettings` 。但是使用更方便。

参考 [生成一个 Qt on Android 项目]()，我们一定要在 `C++` 设置应用的应用名，组织名，以及域名。

```C++
#include <QApplication>
#include <QQmlApplicationEngine>

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

```

然后才可以在 QML 中使用如下语句。

```qml
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

上面示例，在调整应用窗体大小关闭在重启，可以恢复到之前的大小。

用这个 Settings 可以记录应用程序开启的次数。

虽然使用数据库更好，但是相对于 Settings 来说，太复杂了。

记录程序启动次数如下：

```qml
import QtQuick.Window 2.1
import Qt.labs.settings 1.0

Window {
    id: window

    property int openApplicationCount: 0
    width: 800
    height: 600

    Settings {
        property alias openApplicationCount: window.openApplicationCount
    }

    // 应用启动一次，就加载此页面一次，就记录一次启动。
    Component.onCompleted: window.openApplicationCount++;  
}
```

这样就可以简单的记录应用启动的次数了。

## 实现

在 [SplashScreen](E:\github\A-week-to-develop-android-app-plan\demos\SplashScreen\doc\readme.md) 已经说明了，QML 实现的 SplashScreen 更适合做为引导页。

一般需要设置 `modality`,`flags`,`visibility`，添加一个信号，提示引导完成。

```qml
Window {
    id: guide
    signal guideFinished()

    title: qsTr("Guide")

    visible: true
    color: "transparent"
    modality: Qt.ApplicationModal
    flags: Qt.SplashScreen
    visibility: Window.FullScreen
```

内部使用一个滚动方向设置为水平的 `ListView` 作为引导视图。

```qml
    ListView {
        id: guideView
        
        anchors.fill: parent
        highlightRangeMode: ListView.StrictlyEnforceRange
        snapMode: ListView.SnapOneItem
        boundsBehavior: ListView.StopAtBounds
        orientation: ListView.Horizontal
```

使用 `VisualItemModel` 存放引导页面。

```qml
    VisualItemModel {
        id: guidePages

        Rectangle {
            width: guide.width
            height: guide.height
            color: "red"
            Text{
                anchors.centerIn: parent
                font.family: "微软雅黑"
                text: guide.openApplicationCount
            }
        }

        Rectangle {
            width: guide.width
            height: guide.height
            color: "blue"
        }

        Rectangle {
            width: guide.width
            height: guide.height

            Button{
                anchors.centerIn: parent
                text: "Guide Finished"
                onClicked: {
                    guideFinished();
                }
            }
        }
    }
```

别忘记和 Settings 配合使用。

```qml
    property int openApplicationCount: 0

    Settings {
        property alias openApplicationCount: guide.openApplicationCount
    }
    ......
    Component.onCompleted: {
        guide.openApplicationCount++;
    }
```

入口 QML 文件如下：

```qml
import QtQuick 2.4
import QtQuick.Window 2.0

QtObject {
    id: main

    property var guide: Guide {
        id: _guide
    }

    property var mainWindow: MainWindow {
        id: _mainWindow
        visible: false
    }

    Component.onCompleted: {
//        if(_guide.openApplicationCount > 0) {
//            _mainWindow.visible = true;
//            _guide.destroy();
//        }
        _guide.guideFinished.connect(function(){
            _guide.guideFinished.disconnect(arguments.callee);
            _mainWindow.visible = true;
            _guide.destroy();
        });
    }
}
```

实际上，看起来代码很多，但是在设计和使用的时候更具灵活性。可以添加动画，粒子特效，3D 特效到引导页面中。
