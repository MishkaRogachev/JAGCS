import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtPositioning 5.6
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../DashboardControls" as DashboardControls

RowLayout {
    id: root

    property alias command: radiusBox.command
    property alias tipText: radiusBox.tipText

    spacing: sizings.spacing

    Connections {
        target: vehicleDisplay
        onUpdateCommandStatus: if (command == root.command) radiusBox.status = status;
    }

    Connections {
         target: vehicle.navigator
         onTargetDistanceChanged: {
             if (radiusBox.isValid) return;
             radiusBox.realValue = vehicle.navigator.targetDistance;
         }
    }

    Component.onCompleted: radiusBox.realValue = vehicle.navigator.targetDistance

    DashboardControls.Label { text: qsTr("Rad. m") }

    DashboardControls.CommandRealSpinBox {
        id: radiusBox
        realTo: settings.value("Parameters/maxRadius")
        precision: 1 // TODO: radius precision to settings
        Layout.fillWidth: true
    }
}
