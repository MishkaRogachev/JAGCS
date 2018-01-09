import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Pane {
    id: root

    property int count: missionItems
    property int status: Command.Idle

    property alias current: itemBox.currentIndex

    function updateCommandStatus(command, status) {
        switch (command) {
        case Command.GoTo:
            root.status = status;
            if (status === Command.Completed || status === Command.Rejected) timer.start()
            break;
        default:
            break;
        }
    }

    function goTo(index) {
        presenter.executeCommand(Command.GoTo, [ index ]);
    }

    function updateItems() {
        var items = [];
        for (var i = 0; i < count; ++i) items.push(i + 1);
        itemBox.model = items;
    }

    Component.onCompleted: updateItems()
    onCountChanged: updateItems()

    enabled: online

    Timer {
        id: timer
        onTriggered: status = Command.Idle
    }

    RowLayout {
        anchors.centerIn: parent
        width: parent.width
        spacing: sizings.spacing

        Controls.Label {
            text: qsTr("WP")
            Layout.fillWidth: true
        }

        Controls.Button {
            tipText: qsTr("Goto left")
            iconSource: "qrc:/icons/left.svg"
            enabled: current > 1
            onClicked: goTo(current - 1)
        }

        Controls.ComboBox {
            id: itemBox
            currentIndex: count
            onActivated: goTo(index)
            contentColor: status == Command.Idle ? palette.textColor: palette.selectedTextColor
            horizontalAlignment: Text.AlignHCenter
            Layout.preferredWidth: sizings.controlBaseSize * 3

            Rectangle {
                z: -1
                anchors.fill: parent
                radius: 3
                color: {
                    if (status == Command.Rejected) return palette.dangerColor;
                    if (status == Command.Sending) return palette.cautionColor;
                    if (status == Command.Completed) return palette.positiveColor;
                    return "transparent";
                }
            }
        }

        Controls.Button {
            tipText: qsTr("Goto right")
            iconSource: "qrc:/icons/right.svg"
            enabled: current < count - 1
            onClicked: goTo(current + 1)
        }
    }
}
