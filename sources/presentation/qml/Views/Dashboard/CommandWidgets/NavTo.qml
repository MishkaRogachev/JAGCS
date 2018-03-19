import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../DashboardControls" as DashboardControls

GridLayout {
    id: root

    property alias status: sendButton.status

    rowSpacing: sizings.spacing
    columnSpacing: sizings.spacing
    columns: 3
    visible: vehicle.mode === Domain.NavTo

    onVisibleChanged: updateLatLonAlt()
    Component.onCompleted: updateLatLonAlt()

    function updateLatLonAlt() {
        altitudeBox.value = vehicle.barometric.displayedAltitude;
        latitudeBox.value = vehicle.position.latitude;
        longitudeBox.value = vehicle.position.longitude;
    }

    DashboardControls.Label { text: qsTr("Alt.") }

    Controls.SpinBox {
        id: altitudeBox
        to: 20000 // TODO: borderValues
        font.bold: true
        font.pixelSize: sizings.fontPixelSize * 0.6
        Layout.fillWidth: true
    }

    DashboardControls.CommandButton {
        id: sendButton
        command: Command.NavTo
        iconSource: "qrc:/icons/play.svg"
        tipText: qsTr("Send point")
        args: [ latitudeBox.value, longitudeBox.value,
            vehicle.barometric.fromDisplayedAltitude(altitudeBox.value) ]
    }

    DashboardControls.Label { text: qsTr("Lat.") }

    Controls.CoordSpinBox {
        id: latitudeBox
        font.bold: true
        font.pixelSize: sizings.fontPixelSize * 0.6
        Layout.fillWidth: true
    }

    Controls.MapPickButton {
        id: pickButton
        onPicked: {
            latitudeBox.value = coordinate.latitude;
            longitudeBox.value = coordinate.longitude;
            map.pickerCoordinate = coordinate;
        }
        onVisibleChanged: {
            map.pickerVisible = visible;
            picking = false;
        }
        Layout.rowSpan: 2
    }

    DashboardControls.Label { text: qsTr("Lon.") }

    Controls.CoordSpinBox {
        id: longitudeBox
        isLongitude: true
        font.bold: true
        font.pixelSize: sizings.fontPixelSize * 0.6
        Layout.fillWidth: true
    }
}
