import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../DashboardControls" as DashboardControls

RowLayout {
    id: root

    property alias status: sendButton.status

    spacing: sizings.spacing

    onVisibleChanged: updateAlt()
    Component.onCompleted: updateAlt()

    function updateAlt() {
        altitudeBox.value = units.convertDistanceTo(altitudeUnits,
                                                    vehicle.barometric.displayedAltitude);
    }

    DashboardControls.Label {
        text: qsTr("Chg. ALT") + ", " + altitudeSuffix
    }

    Controls.SpinBox {
        id: altitudeBox
        from: -200
        to: 20000 // TODO: borderValues
        font.bold: true
        font.pixelSize: sizings.fontPixelSize * 0.6
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
