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
