import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.LocalStorage 2.0

// Note: This type is made available by importing the Qt.labs.settings module.
// Types in the Qt.labs module are not guaranteed to remain compatible in future versions.
import Qt.labs.settings 1.0

Window {
    id: guide
    signal guideFinished()

    title: qsTr("Guide")

    visible: true
    color: "transparent"
    modality: Qt.ApplicationModal
    flags: Qt.SplashScreen
    visibility: Window.FullScreen

    property int openApplicationCount: 0

    Settings {
        property alias openApplicationCount: guide.openApplicationCount
    }

    ListView {
        id: guideView

        anchors.fill: parent
        highlightRangeMode: ListView.StrictlyEnforceRange
        snapMode: ListView.SnapOneItem
        boundsBehavior: ListView.StopAtBounds
        orientation: ListView.Horizontal
        model: guidePages
        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 30
            height: 30
            spacing: 10
            Repeater {
                model: guideView.count
                anchors.horizontalCenter: parent.horizontalCenter
                Rectangle {
                    width: 15
                    height: 15
                    radius: width / 2
                    color: guideView.currentIndex == index ? "blue":"lightblue"
                    border.color: "black"
                    border.width: 1
                }
            }
        }
    }

    VisualItemModel {
        id: guidePages

        Rectangle {
            width: guide.width
            height: guide.height
            color: "red"
            Text{
                anchors.centerIn: parent
                font.family: "微软雅黑"
                text: guide.openApplicationCount
            }
        }

        Rectangle {
            width: guide.width
            height: guide.height
            color: "blue"
        }

        Rectangle {
            width: guide.width
            height: guide.height

            Button{
                anchors.centerIn: parent
                text: "Guide Finished"
                onClicked: {
                    guideFinished();
                }
            }
        }
    }
    Component.onCompleted: {
        guide.openApplicationCount++;
    }
}
