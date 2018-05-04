import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtPositioning 5.6
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../../DashboardControls" as DashboardControls

GridLayout {
    id: root

    property int command: Command.UnknownCommand

    property alias tipText: sendButton.tipText

    rowSpacing: sizings.spacing
    columnSpacing: sizings.spacing
    columns: 3

    Connections {
        target: display
        onUpdateCommandStatus: if (command == root.command) sendButton.status = status;
    }

    Connections {
        target: vehicle.barometric
        enabled: vehicle.barometric.present
        onDisplayedAltitudeChanged: {
            if (altitudeBox.isValid) return;
            altitudeBox.realValue = units.convertDistanceTo(
                        altitudeUnits, vehicle.barometric.displayedAltitude);
        }
    }

    Connections {
        target: vehicle
        onPositionChanged: {
            if (!latitudeBox.isValid) latitudeBox.value = vehicle.position.latitude;
            if (!longitudeBox.isValid) longitudeBox.value = vehicle.position.longitude;
        }
    }

    onVisibleChanged: {
        altitudeBox.realValue = units.convertDistanceTo(
                    altitudeUnits, vehicle.barometric.displayedAltitude);
        latitudeBox.value = vehicle.position.latitude;
        longitudeBox.value = vehicle.position.longitude;
    }

    DashboardControls.Label { text: qsTr("Alt.") + ", " + altitudeSuffix }

    Controls.RealSpinBox {
        id: altitudeBox
        realFrom: settings.value("Parameters/minAltitude")
        realTo: settings.value("Parameters/maxAltitude")
        precision: settings.value("Parameters/precisionAltitude")
        Layout.fillWidth: true
    }

    DashboardControls.CommandButton {
        id: sendButton
        command: root.command
        iconSource: "qrc:/icons/play.svg"
        args: [ latitudeBox.value, longitudeBox.value,
            vehicle.barometric.fromDisplayedAltitude(altitudeBox.realValue) ]
    }

    //DashboardControls.Label { text: qsTr("Lat.") }

    Controls.CoordSpinBox {
        id: latitudeBox
        font.pixelSize: sizings.fontPixelSize * 0.7
        Layout.fillWidth: true
        Layout.columnSpan: 2
    }

    Controls.MapPickButton { // FIXME: unified picker with planning mode
        id: pickButton
        onPicked: {
            latitudeBox.value = coordinate.latitude;
            longitudeBox.value = coordinate.longitude;
        }
        Layout.rowSpan: 2
    }

    //DashboardControls.Label { text: qsTr("Lon.") }

    Controls.CoordSpinBox {
        id: longitudeBox
        isLongitude: true
        font.pixelSize: sizings.fontPixelSize * 0.7
        Layout.fillWidth: true
        Layout.columnSpan: 2
    }
}
