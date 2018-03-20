import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../DashboardControls" as DashboardControls

RowLayout {
    id: root

    spacing: sizings.spacing

    onVisibleChanged: updateAlt()
    Component.onCompleted: updateAlt()

    function updateAlt() {
        altitudeBox.value = units.convertDistanceTo(altitudeUnits,
                                                    vehicle.barometric.displayedAltitude);
    }

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

    DashboardControls.Label {
        text: qsTr("Chg. ALT") + ", " + altitudeSuffix
    }

    Controls.SpinBox {
        id: altitudeBox
        from: -200
        to: 20000 // TODO: borderValues
        Layout.fillWidth: true
    }

    DashboardControls.CommandButton {
        id: sendButton
        command: Command.ChangeAltitude
        iconSource: "qrc:/icons/play.svg"
        tipText: qsTr("Change altitude")
        args: [ vehicle.barometric.fromDisplayedAltitude(units.convertDistanceFrom(
                                                             altitudeUnits, altitudeBox.value)) ]
        Layout.rowSpan: 2
    }
}
