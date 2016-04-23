import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Open Gallery")

    RowLayout {
        Button {
            text: qsTr("Open Gallery")
            onClicked: {
                openGallery(function(path){
                    text.text = path
                });
            }
        }

        Text {
            id: text
        }
    }

    // callable(path)
    function openGallery(callable, err) {
        callable = callable || function(path){
            console.log("Select Image Path From Gallery: ", path);
        };

        err = err || function(errorMessage){
            console.log("Error Message: ", errorMessage);
        };

        CallNativeGallery.error.connect(function(errorMessage){
            CallNativeGallery.finished.disconnect(arguments.callee);
            err(errorMessage);
        })
        CallNativeGallery.finished.connect(function(path){
            CallNativeGallery.finished.disconnect(arguments.callee);
            callable(path);
        })
        CallNativeGallery.openGallery();
    }
}

