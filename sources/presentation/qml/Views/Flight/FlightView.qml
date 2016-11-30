import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

import "../Map"
import "../Video"

Pane {
    id: root

    property var vehicleNames
    property alias selectedVehicle: vehicleView.vehicle

    signal vehicleSelected(string name)

    RowLayout {
        anchors.fill: parent
        anchors.margins: 5

        ColumnLayout {
            id: toolBar
            Layout.fillHeight: true
            Layout.preferredWidth: 420

            ComboBox {
                model: vehicleNames
                Layout.preferredWidth: parent.width
                onCurrentTextChanged: vehicleSelected(currentText)
                onCountChanged: console.log(count)
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

        VehicleMapView {
            objectName: "map"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
