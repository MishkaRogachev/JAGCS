import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../DashboardControls" as DashboardControls

RowLayout {
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
            case Command.GoTo:
                itemBox.status = status;
                break;
            default:
                break;
            }
        }
    }

    enabled: count > 0
    spacing: sizings.spacing

    DashboardControls.Label {
        text: qsTr("WP")
        Layout.fillWidth: true
    }

    Controls.Button {
        tipText: qsTr("Go to backward")
        iconSource: "qrc:/icons/left.svg"
        enabled: current > 0
        onClicked: itemBox.goTo(current - 1)
    }

    DashboardControls.WaypointBox {
        id: itemBox
        Layout.preferredWidth: sizings.controlBaseSize * 3
    }

    Controls.Button {
        tipText: qsTr("Go to forward")
        iconSource: "qrc:/icons/right.svg"
        enabled: current < count - 1
        onClicked: itemBox.goTo(current + 1)
    }
}
