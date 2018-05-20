import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls

Row {
    id: missionItemList

    property int missionId: 0
    property int selectedItemId: 0
    width: sizings.controlBaseSize * repeater.count

    property alias itemIds: repeater.model

    signal selectionRequest(int itemId)

    onMissionIdChanged: presenter.setMission(missionId)

    MissionItemListPresenter {
        id: presenter
        view: missionItemList
    }

    Controls.Label {
        id: label
        visible: repeater.count == 0
        text: qsTr("No waypoints")
        horizontalAlignment: Qt.AlignHCenter
        width: parent.width
    }

    Repeater {
        id: repeater

        Item {
            width: Math.min(itemView.implicitWidth, missionItemList.width / repeater.count)
            height: itemView.implicitHeight

            MissionItemView {
                id: itemView
                anchors.centerIn: parent
                itemId: modelData
                selected: selectedItemId == itemId
                onPressed: missionItemList.selectionRequest(itemId)
            }
        }
    }
}
