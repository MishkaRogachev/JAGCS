import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper
import "qrc:/Controls" as Controls

import "../../Common"
import "../Command"

BaseDisplay {
    id: root

    property bool guided: false
    property bool downloading: false

    signal downloadMission()
    signal cancelSyncMission()

    implicitHeight: grid.height
    implicitWidth: grid.implicitWidth

    GridLayout {
        id: grid
        anchors.top: parent.top
        width: root.width
        columns: 3

        MissionItemsStatusView {
            id: itemsStatus
            objectName: "itemsStatus"
            Layout.fillWidth: true
            Layout.columnSpan: 2
        }

        Controls.Button {
            iconSource: "qrc:/icons/download.svg"
            enabled: online
            highlighted: downloading
            onClicked: downloading ? cancelSyncMission() : downloadMission()
        }

        Controls.Label {
            Layout.fillWidth: true
            text: itemsStatus.selectedCommand === MissionItem.UnknownCommand ?
                      qsTr("No waypoint") : translator.translateCommand(itemsStatus.selectedCommand)
        }

        CommandButton {
            iconSource: "qrc:/icons/play.svg"
            enabled: online
            command: Command.Start
        }

        CommandButton {
            iconSource: "qrc:/icons/home.svg"
            enabled: online
            command: Command.Return
        }
    }
}
