import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../CommandControls" as CommandControls

Controls.Pane {
    id: root

    property int count: missionItems
    property alias current: itemBox.currentIndex

    function updateCommandStatus(command, status) {
        switch (command) {
        case Command.GoTo:
            itemBox.status = status;
            break;
        default:
            break;
        }
    }

    function updateItems() {
        var items = [];
        for (var i = 0; i < count; ++i) items.push(i + 1);
        itemBox.model = items;
    }

    Component.onCompleted: updateItems()
    onCountChanged: updateItems()

    enabled: online && missionItems > 0

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
            font.pixelSize: sizings.fontPixelSize * 0.7
            font.bold: true
            Layout.fillWidth: true
        }

        Controls.Button {
            tipText: qsTr("Goto left")
            iconSource: "qrc:/icons/left.svg"
            enabled: current > 1
            onClicked: itemBox.goTo(current - 1)
        }

        CommandControls.WaypointBox {
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
}
