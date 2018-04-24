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
            case sendButton.command:
                sendButton.status = status;
                break;
            default:
                break;
            }
        }
    }

    Connections {
         target: vehicle.pitot
         enabled: vehicle.pitot.present
         onIndicatedAirspeedChanged: {
             if (spdBox.isValid) return;
             spdBox.realValue = units.convertSpeedTo(speedUnits, vehicle.pitot.indicatedAirspeed);
         }
    }

    Connections {
         target: vehicle.satellite
         enabled: !vehicle.pitot.present
         onGroundspeedChanged: {
             if (spdBox.isValid) return;
             spdBox.realValue = units.convertSpeedTo(speedUnits, vehicle.satellite.groundspeed);
         }
    }

    onVisibleChanged: {
        spdBox.realValue = units.convertSpeedTo(speedUnits, vehicle.pitot.present ?
                                                    vehicle.pitot.indicatedAirspeed :
                                                    vehicle.satellite.groundspeed);
    }

    DashboardControls.Label {
        text: qsTr("Set") + " " + (vehicle.pitot.present ?qsTr("IAS") : qsTr("GS")) +
              ", " + speedSuffix
    }

    Controls.RealSpinBox {
        id: spdBox
        realFrom: settings.value("Parameters/minSpeed")
        realTo: settings.value("Parameters/maxSpeed")
        precision: settings.value("Parameters/precisionSpeed")
        Layout.fillWidth: true
    }

    DashboardControls.CommandButton {
        id: sendButton
        command: vehicle.pitot.present ? Command.SetAirspeed : Command.SetGroundspeed
        iconSource: "qrc:/icons/play.svg"
        tipText: vehicle.pitot.present ? qsTr("Set Airspeed") : qsTr("Set Groundspeed")
        args: [ units.convertSpeedFrom(speedUnits, spdBox.realValue) ]
        Layout.rowSpan: 2
    }
}
