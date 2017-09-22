import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper
import "qrc:/Controls" as Controls

BaseDisplay {
    id: root

    property int waypoint: 0
    property alias waypoints: waypointBox.model

    property bool armed: false
    property bool guided: false
    property bool downloading: false

    signal setWaypoint(int item)
    signal downloadMission()
    signal cancelSyncMission()

    onWaypointChanged: waypointBox.currentIndex = waypointBox.model.indexOf(waypoint.toString())

    implicitHeight: grid.height
    implicitWidth: grid.implicitWidth

    GridLayout {
        id: grid
        anchors.top: parent.top
        width: root.width
        columns: 3

        Controls.Label {
            text: qsTr("WP:")
            font.pixelSize: palette.fontPixelSize * 0.7
            font.bold: true
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            id: waypointBox
            model: []
            onCurrentTextChanged: setWaypoint(currentText)
            enabled: guided
            Layout.fillWidth: true
        }

        Controls.Button {
            iconSource: "qrc:/icons/download.svg"
            highlighted: downloading
            onClicked: downloading ? cancelSyncMission() : downloadMission()
        }
    }
}
