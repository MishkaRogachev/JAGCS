import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

ColumnLayout {
    id: missionEdit

    property int missionId: 0

    implicitWidth: sizings.controlBaseSize * 11

    MissionItemListView {
        missionId: missionEdit.missionId
        Layout.fillWidth: true
    }

    MissionItemEditView {
        missionId: missionEdit.missionId
        Layout.fillWidth: true
        Layout.fillHeight: true
    }
}

