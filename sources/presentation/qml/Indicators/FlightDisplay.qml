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

    property int minClimb: -3
    property int maxClimb: 3
    property int climbStep: 1

    Behavior on climb { PropertyAnimation { duration: 100 } }

    Row {
        spacing: 1

        ArtificialHorizont {
            id: horizont
            anchors.verticalCenter: parent.verticalCenter
            width: root.width * 0.9
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

        LinearScale {
            id: groundSpeedScale
            anchors.verticalCenter: parent.verticalCenter
            width: root.width * 0.1 - 1
            height: root.height * 0.6
            fontPixelSize: palette.fontPixelSize * 0.6
            value: climb
            minValue: climb + minClimb
            maxValue: climb + maxClimb
            valueStep: climbStep
            canvasRotation: 90
        }
    }
}
