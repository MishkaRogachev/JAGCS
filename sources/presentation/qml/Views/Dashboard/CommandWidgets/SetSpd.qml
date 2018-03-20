import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../DashboardControls" as DashboardControls

RowLayout {
    id: root

    property alias command: sendButton.command
    property alias status: sendButton.status

    spacing: sizings.spacing

    onVisibleChanged: updateSpd()
    Component.onCompleted: updateSpd()

    function updateSpd() {
        spdBox.realValue = units.convertSpeedTo(speedUnits, vehicle.pitot.present ?
                                                    vehicle.pitot.indicatedAirspeed :
                                                    vehicle.satellite.groundSpeed);
    }

    DashboardControls.Label {
        text: qsTr("Set") + " " + (vehicle.pitot.present ?qsTr("IAS") : qsTr("GS")) +
              ", " + speedSuffix
    }

    Controls.RealSpinBox {
        id: spdBox
        realTo: 1000 // TODO: borderValues
        font.bold: true
        font.pixelSize: sizings.fontPixelSize * 0.6
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
