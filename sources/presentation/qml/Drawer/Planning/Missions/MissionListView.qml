import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

Item {
    id: missionList

    property alias missions: list.model

    onVisibleChanged: drawer.filterEnabled = visible
    Component.onCompleted: if (visible) drawer.filterEnabled = true

    Connections{
        target: drawer
        onFilter: presenter.filter(text)
    }

    MissionListPresenter {
        id: presenter
        view: missionList
    }

    ListView {
        id: list
        anchors.fill: parent
        anchors.margins: industrial.shadowSize
        anchors.bottomMargin: addButton.height
        spacing: industrial.spacing
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds

        Controls.ScrollBar.vertical: Controls.ScrollBar {
            visible: parent.contentHeight > parent.height
        }

        delegate: MissionView {
            width: parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            missionId: model.missionId
        }
    }

    Controls.Label {
        anchors.centerIn: parent
        text: qsTr("No missions present")
        visible: list.count === 0
    }

    Controls.FloatButton {
        id: addButton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        highlighted: true
        iconSource: "qrc:/ui/plus.svg"
        tipText: qsTr("Add Mission")
        onClicked: presenter.addMission(map.centerOffsetted)
    }
}
