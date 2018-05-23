import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../../DashboardControls" as DashboardControls

BaseInstrument {
    id: root

    readonly property int count: vehicle.mission.count
    readonly property int current: vehicle.mission.current

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
        target: display
        onUpdateCommandStatus: {
            switch (command) {
            case Command.GoTo:
                itemBox.status = status;
                break;
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

    GridLayout {
        anchors.fill: parent
        columns: 2
        rowSpacing: sizings.spacing
        columnSpacing: sizings.spacing

        DashboardControls.Label {
            text: qsTr("WP")
            Layout.fillWidth: true
        }

        DashboardControls.WaypointBox {
            id: itemBox
            enabled: count > 0
            Layout.preferredWidth: sizings.controlBaseSize * 4
            Layout.rightMargin: itemMenuButton.width
            Layout.fillWidth: true

            Controls.Button {
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                flat: true
                tipText: qsTr("Go to backward")
                iconSource: "qrc:/icons/left.svg"
                enabled: current > 0
                onClicked: itemBox.goTo(current - 1)
            }

            Controls.Button {
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                flat: true
                tipText: qsTr("Go to forward")
                iconSource: "qrc:/icons/right.svg"
                enabled: current < count - 1
                onClicked: itemBox.goTo(current + 1)
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
}
