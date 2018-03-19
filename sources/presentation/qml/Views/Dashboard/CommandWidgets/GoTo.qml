import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls
import "../DashboardControls" as DashboardControls

RowLayout {
    id: root

    property int count: vehicle.mission.count
    property int current: vehicle.mission.current

    property alias status: itemBox.status

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
