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

        CommandWidgets.ModeControl {}

        CommandWidgets.GoTo {
            visible: vehicle.mode === Domain.Mission
        }

        CommandWidgets.NavTo {
            visible: vehicle.mode === Domain.NavTo
        }

        CommandWidgets.ChangeAlt {
            visible: vehicle.mode === Domain.Circle ||
                     vehicle.mode === Domain.Loiter ||
//                     vehicle.mode === Domain.Mission ||
                     vehicle.mode === Domain.Return
        }

        CommandWidgets.SetSpd {
            visible: vehicle.mode === Domain.Mission ||
                     vehicle.mode === Domain.NavTo
        }

        CommandWidgets.LandControl {
            visible: vehicle.mode === Domain.Mission
        }

//        CommandWidgets.PreparationControl {
//             visible: !vehicle.armed // TODO: to preparation panel
//        }
    }
}
