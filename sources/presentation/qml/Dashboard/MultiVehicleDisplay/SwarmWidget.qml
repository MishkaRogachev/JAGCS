import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import Industrial.Indicators 1.0 as Indicators

import "../DashboardControls" as DashboardControls

Controls.Pane {
    id: widget

    property bool lastSwarmCommand: false

    Connections {
        target: listDisplay
        ignoreUnknownSignals: true
        onUpdateCommandStatus: {
            switch (command) {
            case Command.SwitchSwarmMode:
                lastSwarmCommand ? swarmingOff.status = status :
                                   swarmingOn.status = status;
                break;
            default:
                break;
            }
        }
    }

    RowLayout {
        anchors.centerIn: parent
        width: parent.width
        spacing: 1

        DashboardControls.Label {
            text: qsTr("Global Swarming")
            font.pixelSize: controlSize.fontSize
            Layout.fillWidth: true
        }

        DashboardControls.CommandButton {
            id: swarmingOn
            text: qsTr("ON")
            args: [ true ]
            command: Command.SwitchSwarmMode
            onClicked: {
                swarmingOff.status = Command.Idle;
                lastSwarmCommand = false;
            }
        }

        DashboardControls.CommandButton {
            id: swarmingOff
            text: qsTr("OFF")
            args: [ false ]
            command: Command.SwitchSwarmMode
            onClicked: {
                swarmingOn.status = Command.Idle;
                lastSwarmCommand = true;
            }
        }
    }
}
