import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls
import "../../Common"

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
    }
}
