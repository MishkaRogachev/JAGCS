import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../DashboardControls" as DashboardControls

RowLayout {
    id: root

    spacing: sizings.spacing

    Connections {
        target: vehicleDisplay
        onUpdateCommandStatus: {
            switch (command) {
            case Command.ChangeAltitude:
                sendButton.status = status;
                break;
            default:
                break;
            }
        }
    }

    Connections {
        target: vehicle.barometric
        enabled: vehicle.barometric.present
        onDisplayedAltitudeChanged: {
            if (altitudeBox.isValid) return;
            altitudeBox.realValue = units.convertDistanceTo(altitudeUnits,
                                                            vehicle.barometric.displayedAltitude);
        }
    }

    onVisibleChanged: {
        altitudeBox.realValue = units.convertDistanceTo(altitudeUnits,
                                                        vehicle.barometric.displayedAltitude);
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
        command: Command.ChangeAltitude
        iconSource: "qrc:/icons/play.svg"
        tipText: qsTr("Change altitude")
        args: [ vehicle.barometric.fromDisplayedAltitude(units.convertDistanceFrom(
                                                             altitudeUnits, altitudeBox.realValue)) ]
        Layout.rowSpan: 2
    }
}
