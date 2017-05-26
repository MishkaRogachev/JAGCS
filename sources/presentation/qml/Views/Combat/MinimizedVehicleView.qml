import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtCharts 2.0
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

Controls.Frame {
    id: root

    property string name
    property int mavId

    property bool armed
    property string modeString

    property real pitch
    property real roll
    property real yaw

    signal maximize()

    RowLayout {
        id: row
        anchors.fill: parent

        Indicators.ArtificialHorizon {
            id: af
            armed: root.armed
            pitch: root.pitch
            roll: root.roll
            Layout.minimumWidth: palette.controlBaseSize * 2
        }

        Indicators.Compass {
            id: compass
            Layout.minimumWidth: palette.controlBaseSize * 3
        }

        ColumnLayout {

            Controls.Label {
                text: qsTr("MAV") + ": " + name
            }

            Controls.Label {
                text: qsTr("MAV ID") + ": " + mavId
            }

            Controls.Label {
                text: qsTr("Mode") + ": " + modeString
            }
        }

        Controls.Button {
            anchors.right: parent.right
            anchors.top: parent.top
            iconSource: "qrc:/ui/plus.svg"
            onClicked: maximize()
        }
    }
}

