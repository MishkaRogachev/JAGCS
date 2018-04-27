import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../CommandWidgets" as CommandWidgets

Controls.Pane {
    id: root

    enabled: vehicle.online

    ColumnLayout {
        anchors.fill: parent
        spacing: sizings.spacing

        CommandWidgets.Calibrations {
            enabled: !vehicle.armed
        }

        CommandWidgets.SetPoint {
            command: Command.SetReturn
            tipText: qsTr("Set return point")
        }
    }
}

