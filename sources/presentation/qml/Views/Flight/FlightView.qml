import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

import "../Video"

Pane {
    id: root

    property var vehicleNames
    property alias selectedVehicle: vehicleView.vehicle

    signal vehicleSelected(string name)

    padding: 0

    RowLayout {
        anchors.fill: parent
        anchors.margins: 5

        ColumnLayout {
            id: toolBar
            Layout.fillHeight: true
            Layout.preferredWidth: 420 // TODO: dynamic width

            ComboBox {
                model: vehicleNames
                Layout.preferredWidth: parent.width
                onCurrentTextChanged: vehicleSelected(currentText)
            }

            VehicleView {
                id: vehicleView
                Layout.preferredWidth: parent.width
            }

            Item {
                width: 1
                Layout.fillHeight: true
            }

            VideoView {
                objectName: "video"
                Layout.preferredWidth: parent.width
                Layout.preferredHeight: width * 3 / 4
            }
        }

        FlightMapView {
            id: map
            objectName: "map"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
