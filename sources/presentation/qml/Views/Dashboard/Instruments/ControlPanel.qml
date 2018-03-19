import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../DashboardControls" as DashboardControls
import "../CommandWidgets" as CommandWidgets

Controls.Pane {
    id: root

    property int count: vehicle.mission.count
    property int current: vehicle.mission.current

    Component.onCompleted: updateItems()
    onCurrentChanged: updateCurrent()
    onCountChanged: updateItems()

    function updateItems() {
        var items = [];
        for (var i = 0; i < count; ++i) items.push(i + 1);
        itemBox.model = items;
    }

    function updateCurrent() {
        itemBox.currentIndex = vehicle.mission.current;
    }

    Connections {
        target: vehicleDisplay
        onUpdateCommandStatus: {
            switch (command) {
            case Command.ArmDisarm:
                armDisarm.status = status;
                break;
            case Command.SetMode:
                modeBox.status = status;
                break;
            case Command.Return:
                rtl.status = status;
                break;
            case Command.GoTo:
                itemBox.status = status;
                break;
            case Command.NavTo:
                navTo.status = status;
                break;
            default:
                break;
            }
        }
    }

    enabled: vehicle.online

    ColumnLayout {
        anchors.fill: parent
        spacing: sizings.spacing

        RowLayout {
             spacing: sizings.spacing

             DashboardControls.DelayCommandButton {
                 id: armDisarm
                 text: vehicle.armed ? qsTr("DISARM") : qsTr("ARM")
                 args: [ !vehicle.armed ]
                 command: Command.ArmDisarm
                 Layout.preferredWidth: sizings.controlBaseSize * 2
             }

             DashboardControls.ModeBox {
                 id: modeBox
                 mode: vehicle.mode
                 model: vehicle.availableModes
                 Layout.fillWidth: true
             }

             DashboardControls.CommandButton {
                 id: rtl
                 tipText: qsTr("Return to launch")
                 iconSource: "qrc:/icons/home.svg"
                 command: Command.Return
                 Layout.alignment: Qt.AlignRight
             }
        }

        RowLayout {
            enabled: count > 0
            spacing: sizings.spacing
            visible: vehicle.mode === Domain.Mission

            DashboardControls.Label {
                text: qsTr("WP")
                Layout.fillWidth: true
            }

            Controls.Button {
                tipText: qsTr("Goto left")
                iconSource: "qrc:/icons/left.svg"
                enabled: current > 1
                onClicked: itemBox.goTo(current - 1)
            }

            DashboardControls.WaypointBox {
                id: itemBox
                Layout.preferredWidth: sizings.controlBaseSize * 3
            }

            Controls.Button {
                tipText: qsTr("Goto right")
                iconSource: "qrc:/icons/right.svg"
                enabled: current < count - 1
                onClicked: itemBox.goTo(current + 1)
            }
        }

        CommandWidgets.NavTo {
            id: navTo
            visible: vehicle.mode === Domain.NavTo
        }
    }
}
