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

    signal minimize()

    ColumnLayout {
        anchors.fill: parent

        Controls.Label {
            text: qsTr("MAV") + ": " + name
        }

        Controls.Label {
            text: qsTr("MAV ID") + ": " + mavId
        }

        Controls.Label {
            text: qsTr("Mode") + ": " + modeString
        }

        Indicators.FlightDirector {
            armed: root.armed
            pitch: root.pitch
            roll: root.roll
            Layout.fillWidth: true
            speedPrefix: qsTr("IAS, m/s")
            altitudePrefix: qsTr("Hbar, m")
        }

        Indicators.Compass {
            id: compass
            Layout.fillWidth: true
        }

        Controls.Button {
            anchors.right: parent.right
            anchors.top: parent.top
            iconSource: "qrc:/ui/minus.svg"
            onClicked: minimize()
        }
    }
}


