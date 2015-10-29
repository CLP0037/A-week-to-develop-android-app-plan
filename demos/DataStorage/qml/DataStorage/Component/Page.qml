import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

ScrollView {
    id: page

    focus: true

    property string title: ""

    horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff

    default property alias data: grid.data

    property alias columnSpacing : grid.columnSpacing
    property alias columns : grid.columns
    property alias flow : grid.flow
    property alias layoutDirection : grid.layoutDirection
    property alias rowSpacing : grid.rowSpacing
    property alias rows : grid.rows

    Item {
        id: content

        width: Math.max(page.viewport.width, grid.implicitWidth + 2 * grid.rowSpacing)
        height: Math.max(page.viewport.height, grid.implicitHeight + 2 * grid.columnSpacing)

        GridLayout {
            id: grid

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: grid.rowSpacing
            anchors.rightMargin: grid.rowSpacing
            anchors.topMargin: grid.columnSpacing

            columns: page.width < page.height ? 1 : 2
        }
    }
}
