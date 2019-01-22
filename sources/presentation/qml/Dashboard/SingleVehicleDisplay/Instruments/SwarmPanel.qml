import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import Industrial.Indicators 1.0 as Indicators
import "../../DashboardControls" as DashboardControls

BaseInstrument {
    id: root

    RowLayout {
        anchors.centerIn: parent
        width: parent.width
        spacing: controlSize.spacing

        DashboardControls.Label {
            text: qsTr("Swarming")
            font.pixelSize: controlSize.fontSize
            Layout.fillWidth: true
        }

        DashboardControls.CommandButton {
            text: qsTr("ENABLE")
            args: [ true ]
            command: Command.SwitchSwarmMode
            Layout.fillWidth: true
        }

        DashboardControls.CommandButton {
            text: qsTr("DISABLE")
            args: [ false ]
            command: Command.SwitchSwarmMode
            Layout.fillWidth: true
        }
    }
}
