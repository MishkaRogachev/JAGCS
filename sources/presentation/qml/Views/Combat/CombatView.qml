import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"
import "../Map"
import "../Video"

Pane {
    id: root

    property var vehicles: []
    property int maximized: -1

    Flickable {
        id: flickable
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        width: column.width
        Layout.margins: palette.margins
        contentHeight: column.height
        clip: true

        ScrollBar.vertical: ScrollBar {}

        ColumnLayout {
            id: column
            spacing: palette.spacing
            width: palette.controlBaseSize * 11

            VehicleView {
                id: vehicleView
                Layout.fillWidth: true
                visible: maximized > -1
                onVisibleChanged: if (visible) vehicles[maximized].setView(vehicleView)
                onMinimize: maximized = -1
            }

            Repeater {
                model: maximized == -1 ? vehicles : []

                MinimizedVehicleView {
                    id: minimizedVehicleView
                    Layout.fillWidth: true
                    Component.onCompleted: modelData.setView(minimizedVehicleView)
                    onMaximize: maximized = index
                }
            }
        }
    }

    MapView {
        id: map
        objectName: "map"
        anchors.left: flickable.right
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: palette.margins
    }
}
