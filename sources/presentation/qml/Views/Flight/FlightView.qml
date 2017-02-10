import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

import "../Video"

Pane {
    id: root

    property QtObject commandHelper
    property var vehicleNames
    property alias selectedVehicle: vehicleView.vehicle

    signal vehicleSelected(string name)

    padding: 0

    FlightMapView {
        id: map
        objectName: "map"
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: sidebar.right
        anchors.right: parent.right
    }

    Item {
        id: sidebar
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: column.width

        ColumnLayout {
            id: column
            height: parent.height

            ComboBox {
                model: vehicleNames
                Layout.fillWidth: true
                onCurrentTextChanged: vehicleSelected(currentText)
            }

            VehicleView {
                id: vehicleView
                Layout.fillWidth: true
            }

            Item {
                width: 1
                Layout.fillHeight: true
            }

            VideoView {
                objectName: "video"
                Layout.fillWidth: true
                Layout.preferredHeight: width * 3 / 4
            }
        }
    }
}
