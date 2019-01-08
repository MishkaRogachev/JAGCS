import QtQuick 2.6
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import "qrc:/Views/Common"

Row {
    id: missionItemList

    property int missionId: 0
    property int selectedItemId: 0

    property alias items: repeater.model

    signal selectionRequest(int itemId)
    signal checkItemX(real x)

    onMissionIdChanged: presenter.setMission(missionId)

    width: industrial.baseSize * repeater.count
    clip: true

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

            PointView {
                id: itemView
                anchors.centerIn: parent
                selected: selectedItemId === model.itemId
                sequence: model.sequence
                command: model.command
                reached: model.reached
                status: model.status
                onSelectedChanged: checkX()

                MouseArea {
                    anchors.fill: parent
                    onClicked: missionItemList.selectionRequest(model.itemId)
                }

                function checkX() {
                    if (visible && selected) checkItemX(parent.x);
                }
            }

            onXChanged: if (x > 0) itemView.checkX()
        }
    }
}
