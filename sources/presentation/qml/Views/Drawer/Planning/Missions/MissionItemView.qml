import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "qrc:/Views/Common"

PointView {
    id: missionItem

    property int itemId: 0

    signal clicked()

    MissionItemPresenter {
        id: presenter
        view: missionItem
        Component.onCompleted: setItem(itemId)
    }

    MouseArea {
        anchors.fill: parent
        onClicked: missionItem.clicked()
    }
}

