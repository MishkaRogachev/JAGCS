import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

ColumnLayout {
    id: root

    property bool armed: false
    property int waypoint: 0

    signal commandArmDisarm(bool arm)
    signal commandReturn()
    signal commandStart()
    signal commandJumpTo(int item)

    RowLayout {
        Controls.Switch {
            text: armed ? qsTr("DISARM") : qsTr("ARM")
            inputChecked: armed
            onCheckedChanged: commandArmDisarm(checked)
            Layout.fillWidth: true
            font.pixelSize: root.width * 0.06
            font.bold: true
        }

        Controls.Button {
            iconSource: "qrc:/icons/home.svg"
            onClicked: commandReturn()
        }

        Controls.Button {
            iconSource: "qrc:/icons/play.svg"
            onClicked: commandStart()
        }
    }

    RowLayout {
        Item {
            Layout.fillWidth: true
        }

        Controls.Button {
            iconSource: "qrc:/icons/left.svg"
            onClicked: commandJumpTo(waypoint - 1)
        }

        Controls.Label {
            text: qsTr("WP: ") + waypoint
            font.pixelSize: root.width * 0.06
            font.bold: true
        }

        Controls.Button {
            iconSource: "qrc:/icons/right.svg"
            onClicked: commandJumpTo(waypoint + 1)
        }
    }
}
