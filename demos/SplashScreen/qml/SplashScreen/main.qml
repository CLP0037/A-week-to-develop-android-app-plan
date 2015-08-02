import QtQuick 2.4

QtObject  {

    property var splashWindow: SplashScreen {
        onTimeout: mainWindow.visible = true
    }
    property var mainWindow: MainWindow{
        id: mainWindow
    }
}
