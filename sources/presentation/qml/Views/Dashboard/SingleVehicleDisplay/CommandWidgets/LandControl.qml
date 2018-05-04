import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../../DashboardControls" as DashboardControls

RowLayout {
    id: root

    spacing: sizings.spacing

    Connections {
        target: display
        onUpdateCommandStatus: {
            switch (command) {
            case Command.Land:
                landButton.status = status;
                break;
            case Command.GoAround:
                goAroundButton.status = status;
                break;
            default:
                break;
            }
        }
    }

    DashboardControls.CommandButton {
        id: landButton
        command: Command.Land
        iconSource: "qrc:/icons/landing.svg"
        text: qsTr("Landing")
        args: []
        Layout.fillWidth: true
    }

    DashboardControls.CommandButton {
        id: goAroundButton
        command: Command.GoAround
        iconSource: "qrc:/icons/go_around.svg"
        text: qsTr("Go around")
        args: []
        Layout.fillWidth: true
    }
}
