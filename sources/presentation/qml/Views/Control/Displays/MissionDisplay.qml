import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper
import "qrc:/Controls" as Controls

import "../../Common"
import "../Command"

BaseDisplay {
    id: root

    property bool armed: false
    property bool guided: false
    property bool downloading: false

    signal setWaypoint(int item)
    signal downloadMission()
    signal cancelSyncMission()

    implicitHeight: grid.height
    implicitWidth: grid.implicitWidth

    GridLayout {
        id: grid
        anchors.top: parent.top
        width: root.width
        columns: 4

        MissionItemsStatusView {
            id: itemsStatus
            objectName: "itemsStatus"
            Layout.fillWidth: true
            Layout.columnSpan: 3
        }

        Controls.Button {
            iconSource: "qrc:/icons/download.svg"
            highlighted: downloading
            onClicked: downloading ? cancelSyncMission() : downloadMission()
        }

        Controls.Label { // TODO: Waypoint short & mode
            Layout.fillWidth: true
            text: qsTr("WP:") + " " + (itemsStatus.selectedItem > -1 ? itemsStatus.selectedItem : "-")
        }

        Controls.Button {
            iconSource: "qrc:/icons/right.svg"
            onClicked: setWaypoint(itemsStatus.selectedItem)
            enabled: itemsStatus.selectedItem > -1
        }

        CommandButton {
            iconSource: "qrc:/icons/play.svg"
            command: Command.Start
        }

        CommandButton {
            iconSource: "qrc:/icons/home.svg"
            command: Command.Return
        }
    }
}
