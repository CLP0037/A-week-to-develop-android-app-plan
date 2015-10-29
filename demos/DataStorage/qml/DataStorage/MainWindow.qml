import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

ApplicationWindow {
    id: mainWindow
    title: qsTr("Data Storage")
    width: 640
    height: 480
    visible: true

    toolBar: ToolBar {
        RowLayout {
            anchors.fill: parent
            anchors.margins: spacing
            Label {
                text: mainWindow.title
            }
            Item { Layout.fillWidth: true }
        }
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("E&xit")
                onTriggered:{
                    Qt.quit();
                }
            }
        }
    }

    TabView {
        id: tabView

        anchors.fill: parent
        anchors.margins: 2
        tabPosition: Qt.BottomEdge

        Layout.minimumWidth: 360
        Layout.minimumHeight: 360
        Layout.preferredWidth: 480
        Layout.preferredHeight: 640
        Tab {
            title: "Settings Example"
            source: "./WellCome/WellCome.qml"
        }
    }
}
