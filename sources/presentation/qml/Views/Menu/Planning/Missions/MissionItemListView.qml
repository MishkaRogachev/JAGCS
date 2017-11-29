import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Flickable {
    id: missionItemList

    property int missionId: 0
    property int selectedItemId: 0
    property var itemIds: []

    signal selectionRequest(int itemId)

    contentWidth: row.width
    implicitWidth: row.width
    implicitHeight: row.height
    boundsBehavior: Flickable.StopAtBounds
    clip: true

    MissionItemListPresenter {
        id: presenter
        view: missionItemList
        Component.onCompleted: setMission(missionId)
    }

    RowLayout {
        id: row
        spacing: 1

        Controls.Label {
            visible: itemIds.length === 0
            text: qsTr("No waypoints")
            horizontalAlignment: Text.AlignHCenter
            Layout.preferredWidth: missionItemList.width
        }

        Repeater {
            model: itemIds

             MissionItemView {
                 itemId: modelData
                 selected: selectedItemId == itemId
                 onSelectionRequest: missionItemList.selectionRequest(itemId)
             }
        }
    }
}
