import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../CommandWidgets" as CommandWidgets

BaseInstrument {
    id: root

    ColumnLayout {
        anchors.fill: parent
        spacing: sizings.spacing

        CommandWidgets.Calibrations {
            enabled: !vehicle.armed
            Layout.rightMargin: itemMenuButton.width
        }

        CommandWidgets.SetPoint {
            command: Command.SetReturn
            enabled: vehicle.mode !== Domain.Return
            tipText: qsTr("Set return point")
        }
    }
}

