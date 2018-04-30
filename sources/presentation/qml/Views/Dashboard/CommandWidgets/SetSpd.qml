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
        onUpdateCommandStatus: if (command == spdBox.command) spdBox.status = status;
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

    onVisibleChanged: spdBox.realValue = units.convertSpeedTo(speedUnits, vehicle.pitot.present ?
                                                                  vehicle.pitot.indicatedAirspeed :
                                                                  vehicle.satellite.groundspeed);

    DashboardControls.Label {
        text: qsTr("Set") + " " + (vehicle.pitot.present ?qsTr("IAS") : qsTr("GS")) +
              ", " + speedSuffix
        Layout.fillWidth: true
    }

    DashboardControls.CommandRealSpinBox {
        id: spdBox
        command: vehicle.pitot.present ? Command.SetAirspeed : Command.SetGroundspeed
        args: [ units.convertSpeedFrom(speedUnits, realValue) ]
        tipText: vehicle.pitot.present ? qsTr("Set airspeed") : qsTr("Set groundspeed")
        realFrom: settings.value("Parameters/minSpeed")
        realTo: settings.value("Parameters/maxSpeed")
        precision: settings.value("Parameters/precisionSpeed")
        Layout.preferredWidth: sizings.controlBaseSize * 4
    }
}
