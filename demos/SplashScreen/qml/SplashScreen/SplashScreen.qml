import QtQuick 2.0
import QtQuick.Window 2.1
/*
 * In mobile platform, splash must full screen
 * In desktop platform, splash half
*/

Window {
    id: splash

    title: "Splash Window"
    color: "transparent"
    modality: Qt.ApplicationModal
    flags: Qt.SplashScreen

    property int timeoutInterval: 2000
    signal timeout

    //    x: (Screen.width - splashItem.width) / 2
    //    y: (Screen.height - splashItem.height) / 2

    width: Screen.width * __screen();
    height: Screen.height * __screen();

    //! [timer]
    Timer {
        interval: timeoutInterval; running: true; repeat: false
        onTriggered: {
            splash.timeout();
//            visible = false;
//            splash.hide();
            splash.destroy()
        }
    }

    //! [timer]
    Component.onCompleted: {
        visible = true;
    }


    Image{
        anchors.fill: parent
        source: "./Qt.gif"

        Text{
            anchors.centerIn: parent
            width: parent.height
            text: "Using the QML to make the splash screen"
            wrapMode: Text.WordWrap
        }

    }

    function __screen(){
        switch(Qt.platform.os)
        {
        case "android":
        case "blackberry":
        case "ios":
            return 1.0;
        case "linux":
        case "osx":
        case "unix":
        case "windows":
        case "wince":
        default:
            return 0.5
        }
    }
}

/*
platform.os	This read-only property contains the name of the operating system.
Possible values are:
"android" - Android
"blackberry" - BlackBerry OS
"ios" - iOS
"linux" - Linux
"osx" - OS X
"unix" - Other Unix-based OS
"windows" - Windows
"wince" - Windows CE
*/

