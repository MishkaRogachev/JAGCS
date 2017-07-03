import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

RowLayout {
    id: root

    property int waypoint: 0
    property bool automatic: false

    signal commandSetWaypoint(int item)
    signal commandReturn()
    signal commandStart()
    signal pauseContinue(bool unpause)

    Controls.Button {
        iconSource: "qrc:/icons/left.svg"
        enabled: automatic
        onClicked: commandSetWaypoint(waypoint - 1)
    }

    Controls.Label {
        text: qsTr("WP: ") + waypoint
        font.pixelSize: palette.fontPixelSize * 0.6
        font.bold: true
    }

    Controls.Button {
        iconSource: "qrc:/icons/right.svg"
        enabled: automatic
        onClicked: commandSetWaypoint(waypoint + 1)
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
        onCheckedChanged: pauseContinue(!checked)
    }
}
