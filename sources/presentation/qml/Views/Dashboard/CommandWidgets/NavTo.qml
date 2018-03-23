import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../DashboardControls" as DashboardControls

GridLayout {
    id: root

    rowSpacing: sizings.spacing
    columnSpacing: sizings.spacing
    columns: 3

    onVisibleChanged: updateLatLonAlt()
    Component.onCompleted: updateLatLonAlt()

    function updateLatLonAlt() {
        altitudeBox.realValue = vehicle.barometric.displayedAltitude;
        latitudeBox.value = vehicle.position.latitude;
        longitudeBox.value = vehicle.position.longitude;
    }

    Connections {
        target: vehicleDisplay
        onUpdateCommandStatus: {
            switch (command) {
            case Command.NavTo:
                sendButton.status = status;
                break;
            default:
                break;
            }
        }
    }

    DashboardControls.Label { text: qsTr("Alt.") }

    Controls.RealSpinBox {
        id: altitudeBox
        realFrom: settings.value("Parameters/minAltitude")
        realTo: settings.value("Parameters/maxAltitude")
        precision: settings.value("Parameters/precisionAltitude")
        Layout.fillWidth: true
    }

    DashboardControls.CommandButton {
        id: sendButton
        command: Command.NavTo
        iconSource: "qrc:/icons/play.svg"
        tipText: qsTr("Nav to")
        args: [ latitudeBox.value, longitudeBox.value,
            vehicle.barometric.fromDisplayedAltitude(altitudeBox.realValue) ]
    }

    DashboardControls.Label { text: qsTr("Lat.") }

    Controls.CoordSpinBox {
        id: latitudeBox
        font.pixelSize: sizings.fontPixelSize * 0.7
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
        font.pixelSize: sizings.fontPixelSize * 0.7
        Layout.fillWidth: true
    }
}
