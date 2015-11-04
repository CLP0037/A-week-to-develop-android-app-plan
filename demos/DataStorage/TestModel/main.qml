import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import Test 1.0

ApplicationWindow {
    title: qsTr("Test Model")
    width: 640
    height: 480
    visible: true

    menuBar: MenuBar {
        Menu {
            title: "Operation"
            MenuItem {
                text: "add..."
                onTriggered: {
                    testModel.addDao("new ", Math.floor(Math.random() * 10));
                }
            }
            MenuItem {
                text: "sort..."
                onTriggered: {
                    testModel.sort();
                }
            }
        }
    }

    ListView {
        id: listView
        anchors.fill: parent
        model: TestModel {
            id: testModel
        }

        delegate: Rectangle {
            width: listView.width
            height: 60
            Text {
                anchors.centerIn: parent
                text: "Name:" + NameRole + " Age:" + AgeRole
            }
        }
    }
}
