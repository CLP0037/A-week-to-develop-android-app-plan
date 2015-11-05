import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

ApplicationWindow {
    id: window
    title: qsTr("Hello World")
    width: 640
    height: 480
    visible: true

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: messageDialog.show(qsTr("Open action triggered"))
            }
            MenuItem {
                text: qsTr("E&xit")
                onTriggered: Qt.quit()
            }
        }
    }

    Item {
        id: root
        anchors.fill: parent

        Rectangle {
            color: "#712727"
            gradient: Gradient {
                GradientStop {
                    position: 0.13
                    color: "#712727"
                }
                GradientStop {
                    position: 1.00
                    color: "#ffffff"
                }
            }
            anchors.fill: parent
            anchors.bottomMargin: bottomBar.height
        }

        Rectangle {
            id: bottomBar
            width: parent.width
            height: 60
            anchors.bottom: parent.bottom

            RowLayout {
                anchors.fill: parent

                Button {
                    text: "save pic"
                    onClicked: {
                        var success = root.grabToImage(function (result) {
                            result.saveToFile("C:/root.png")
                            console.log("pic file path: ", result.url)
                        })
                        console.log("save pic to mem url :", success)
                    }
                }

                TextEdit {
                    id: input
                    Layout.fillWidth: true
                }

                Button {
                    text: "button1"
                    onClicked: {
                        saveTextToFile(input.text,
                                       Qt.resolvedUrl("C:/qml_save_file.txt"))
                    }
                }
            }
        }
    }

    // can't do delete, put, post operation for local file path.
    function saveTextToFile(textContent, filename) {
        var xhr = new XMLHttpRequest()
        xhr.onreadystatechange = function () {
            if (xhr.readyState == xhr.DONE) {
                console.log("DONE")
                console.log(xhr.responseText)
            } else if (xhr.readyState == xhr.HEADERS_RECEIVED) {
                console.log(xhr.getAllResponseHeaders())
            } else {
                console.log(xhr.readyState)
            }
        }
        // xhr.open("PUT", filename, true);
        xhr.open("POST", filename, true)
        xhr.setRequestHeader("Content-Type", "text/html; charset=utf-8")
        xhr.send(textContent)
        console.log(filename, textContent)
    }
}
