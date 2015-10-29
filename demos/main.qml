import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.0

// 圆角图片效果

ApplicationWindow {
    title: qsTr("Hello World")
    width: 640
    height: 480
    visible: true
    color: "#555555"

    Image {
        id: bug
        source: "qrc:/QQ截图20150930185642.png"
        sourceSize: Qt.size(parent.width, parent.height)
        smooth: true
        visible: false
        width: 200
        height:200
        x:20
        y:20

    }

    Rectangle {
        id: mask
        smooth: true
        visible: false
        width: 200
        height: 200
        anchors.centerIn: bug
        radius: width/2
    }

    OpacityMask {
        anchors.fill: bug
        source: bug
        maskSource: mask
    }


    Image {
        id: bug1
        source: "qrc:/bbbbb.png"
        sourceSize: Qt.size(parent.width, parent.height)
        smooth: true
        visible: false
        width: 200
        height:200
        anchors.right:parent.right
        y:20

    }

    Rectangle {
        id: mask1
        smooth: true
        visible: false
        width: 200
        height: 200
        anchors.centerIn: bug1
        radius: width/3
    }

    OpacityMask {
        anchors.fill: bug1
        source: bug1
        maskSource: mask1
    }

}
