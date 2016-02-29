import QtQuick 2.5
import QtQuick.Controls 1.4

ApplicationWindow {
    title: qsTr("Network Image Cache")
    visible: true
    width: 360
    height: 640

    menuBar: MenuBar {
        Menu {
            title: qsTr("Menu")
            MenuItem {
                text: qsTr("&fresh")
                onTriggered: listmodel.getBiliBiliIndex()
            }
        }
    }

    ListView {
        id: view
        maximumFlickVelocity: 5000
        anchors.fill: parent
        model: BiliBiliIndexModel {
            id: listmodel
        }

        delegate: Rectangle {
            width: view.width
            height: view.width * 0.8
            border.color: "black"
            border.width: 1

            Image {
                anchors.fill: parent
                anchors.margins: view.width * 0.01
                source: Pic
            }
        }
    }

    Component.onCompleted: {
        listmodel.getBiliBiliIndex()
    }

}

