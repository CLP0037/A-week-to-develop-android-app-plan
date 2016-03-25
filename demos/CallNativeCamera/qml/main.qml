import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

ApplicationWindow {
    visible: true
    width: 360
    height: 640

    Flickable {
        anchors.fill: parent
        clip: true
        contentHeight: image.height
        contentWidth: image.width
        Image {
            id: image
        }
    }

    RowLayout {
        width: parent.width

        TextField {
            text: qsTr("input some text")
            Layout.fillWidth: true
        }

        Button {
            text:"开启相机"
            onClicked: {
                capture()
            }

            function capture() {
                try {
                    CallNativeCamera.ready.connect(function(path){
                        CallNativeCamera.ready.disconnect(arguments.callee);
                        console.log(path);
                        image.source = path;
                    });
                    CallNativeCamera.error.connect(function(error, errorString){
                        CallNativeCamera.error.disconnect(arguments.callee);
                        console.log("errorCode:", error);
                        console.log("errorString:", errorString);
                    });
                    CallNativeCamera.capture();
                } catch(e) {
                    console.log(e)
                }
            }
        }
    }


}

