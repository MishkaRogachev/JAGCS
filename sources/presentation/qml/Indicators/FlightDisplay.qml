import QtQuick 2.6

import "../Controls"

Column {
    id: root

    property alias pitch: horizont.pitch
    property alias roll: horizont.roll
    property alias airSpeed: horizont.velocity
    property alias altitude: horizont.altitude
    property alias rollInverted: horizont.rollInverted

    property int groundSpeed: 0
    property int snsAltitude: 0
    property int climb: 0

    property int minClimb: -12
    property int maxClimb: 12

    Behavior on climb { PropertyAnimation { duration: 100 } }

    Row {
        spacing: 1

        ArtificialHorizont {
            id: horizont
            anchors.verticalCenter: parent.verticalCenter
            width: root.width * 0.97
            height: width

            Label {
                anchors.top: parent.top
                anchors.left: parent.left
                text: qsTr("GS") + groundSpeed
                width: parent.width * 0.2
                horizontalAlignment: Text.AlignHCenter
            }

            Label {
                anchors.top: parent.top
                anchors.right: parent.right
                text: snsAltitude
                width: parent.width * 0.2
                horizontalAlignment: Text.AlignHCenter
            }
        }

        BarIndicator {
            id: groundSpeedScale
            anchors.verticalCenter: parent.verticalCenter
            width: root.width - horizont.width - 1
            height: root.height * 0.8
            value: climb
            minValue: minClimb
            maxValue: maxClimb
        }
    }
}
