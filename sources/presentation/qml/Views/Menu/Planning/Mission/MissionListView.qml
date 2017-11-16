import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

Repeater {
    id: root

    property var missions: []

    signal addMission()

    model: missions

    MissionView {
        id: missionView
        Layout.fillWidth: true
        Component.onCompleted: modelData.setView(missionView)
    }
}
