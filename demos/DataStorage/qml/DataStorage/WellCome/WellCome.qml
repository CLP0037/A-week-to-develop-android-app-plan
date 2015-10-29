import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import Qt.labs.settings 1.0
import "../Component"

Page {
    id: page
    title: "Well Come"

    Turbulence {
        id: turbulence
        Layout.fillWidth: true
        anchors.centerIn: parent
        flameSize: slider.value
    }

    ColumnLayout {
        anchors.fill: parent
        Layout.fillWidth: true
        Slider {
            id: slider;
            Layout.fillWidth: true
            maximumValue: 600
            minimumValue: 10
            stepSize: 1
            value: 20
            Settings {
                property alias value : slider.value
            }
        }
    }
}
