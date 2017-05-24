import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtCharts 2.0
import JAGCS 1.0

import "qrc:/Controls"
import "qrc:/Indicators" as Indicators

RowLayout {
    id: root

    property string name
    property int mavId

    property alias armed: af.armed
    property string modeString

    property alias pitch: af.pitch
    property alias roll: af.roll
    property alias yaw: compass.heading

    Indicators.ArtificialHorizon {
        id: af
        Layout.minimumWidth: palette.controlBaseSize * 4
    }

    Indicators.Compass {
        id: compass
        Layout.minimumWidth: palette.controlBaseSize * 4
    }

    ColumnLayout {

        Label {
            text: qsTr("MAV") + ": " + name
        }

        Label {
            text: qsTr("MAV ID") + ": " + mavId
        }

        Label {
            text: qsTr("Mode") + ": " + modeString
        }
    }
}
