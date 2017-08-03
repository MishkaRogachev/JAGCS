import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

RowLayout {
    id: root

    property int waypoint: 0
    property var waypoints: []
    property bool guided: false

    signal commandSetWaypoint(int item)
    signal commandReturn()
    signal commandStart()
    signal pauseContinue(bool unpause)

    onWaypointChanged: waypointBox.currentIndex = waypoints.indexOf(waypoint)

    Controls.Label {
        text: qsTr("WP: ")
        font.pixelSize: palette.fontPixelSize * 0.75
        font.bold: true
    }

    Controls.ComboBox {
        id: waypointBox
        model: waypoints
        onCurrentTextChanged: commandSetWaypoint(currentText)
        implicitWidth: palette.controlBaseSize * 2
        enabled: guided
    }

    Item {
        Layout.fillWidth: true
    }

    Controls.Button {
        iconSource: "qrc:/icons/home.svg"
        onClicked: commandReturn()
    }

    Controls.Button {
        iconSource: "qrc:/icons/play.svg"
        onClicked: commandStart()
    }

    Controls.Button {
        iconSource: "qrc:/icons/pause.svg"
        checkable: true
        enabled: guided
        onEnabledChanged: if (!enabled) checked = false;
        onCheckedChanged: pauseContinue(!checked)
    }
}
