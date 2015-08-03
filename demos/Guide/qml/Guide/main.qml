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
