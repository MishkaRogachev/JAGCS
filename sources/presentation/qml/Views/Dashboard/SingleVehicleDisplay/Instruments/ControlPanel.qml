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

        CommandWidgets.GoTo {
            Layout.rightMargin: itemMenuButton.width
        }

        CommandWidgets.SetRadius {
            command: Command.SetLoiterRadius
            tipText: qsTr("Set radius")
            visible: vehicle.mode === Domain.Loiter ||
                     vehicle.mode === Domain.NavTo
        }

        CommandWidgets.LandControl {
            visible: vehicle.mode === Domain.Mission
        }
    }
}
