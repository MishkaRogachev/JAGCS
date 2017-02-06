import QtQuick 2.6

import "../Controls"

Column {
    id: root

    property alias insAvalible: horizont.insAvalible
    property alias pitch: horizont.pitch
    property alias roll: horizont.roll
    property alias indicatedAirSpeed: horizont.velocity
    property alias altitude: horizont.altitude
    property alias rollInverted: horizont.rollInverted
    property alias barometerAvalible: horizont.altitudeAvalible
    property alias airSpeedAvalible: horizont.velocityAvalible

    property bool compassAvalible: true
    property alias heading: compass.heading
    property alias course: compass.course
    property alias windDirection: compass.windDirection

    property alias charge: battery.charge
    property real voltage: 0.0
    property real current: 0.0

    property real trueAirSpeed: 0
    property real windSpeed: 0
    property int groundSpeed: 0
    property int snsAltitude: 0
    property int snsFix: -1
    property color snsColor: {
        switch (snsFix) {
        case 0: return palette.disabledColor;
        case 1: return palette.negativeColor;
        case 2: return palette.neutralColor;
        case 3: return palette.textColor;
        default: return palette.disabledColor;
        }
    }

    property int climb: 0
    property int minClimb: -12
    property int maxClimb: 12

    property bool rangeFinderAvalible: false
    property int geometricAltitude: 0

    property int labelFontSize: palette.fontPixelSize * 0.8
    spacing: 10

    Behavior on climb { PropertyAnimation { duration: 100 } }
    Behavior on heading { PropertyAnimation { duration: 100 } }

    Row {
        spacing: 1
        anchors.horizontalCenter: parent.horizontalCenter

        ArtificialHorizont {
            id: horizont
            anchors.verticalCenter: parent.verticalCenter
            width: root.width * 0.97
            height: width

            Label {
                anchors.top: parent.top
                anchors.left: parent.left
                text: groundSpeed
                font.pixelSize: labelFontSize
                font.bold: true
                width: parent.width * 0.2
                horizontalAlignment: Text.AlignHCenter
                color: snsColor
            }

            Label {
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                text: trueAirSpeed.toFixed(1)
                font.pixelSize: labelFontSize
                font.bold: true
                color: airSpeedAvalible ? palette.textColor : palette.disabledColor
                width: parent.width * 0.2
                horizontalAlignment: Text.AlignHCenter
            }

            Label {
                anchors.top: parent.bottom
                anchors.left: parent.left
                text: qsTr("W") + " " + windSpeed.toFixed(1)
                font.pixelSize: labelFontSize
                font.bold: true
                color: airSpeedAvalible ? palette.textColor : palette.disabledColor
                width: horizont.width * 0.2
                horizontalAlignment: Text.AlignHCenter
            }

            Label {
                anchors.top: parent.top
                anchors.right: parent.right
                text: snsAltitude
                font.pixelSize: labelFontSize
                font.bold: true
                width: parent.width * 0.2
                horizontalAlignment: Text.AlignHCenter
                color: snsColor
            }

            Label {
                anchors.verticalCenter: parent.bottom
                anchors.right: parent.right
                text: geometricAltitude
                font.pixelSize: labelFontSize
                font.bold: true
                width: parent.width * 0.2
                horizontalAlignment: Text.AlignHCenter
                color: rangeFinderAvalible ? palette.textColor : palette.disabledColor
            }
        }

        BarIndicator {
            id: groundSpeedScale
            anchors.verticalCenter: parent.verticalCenter
            width: root.width - horizont.width - 1
            height: horizont.height * 0.8
            value: climb
            fillColor: barometerAvalible ? (value > minValue ?
                                palette.highlightColor : palette.negativeColor) :
                           palette.disabledColor
            minValue: minClimb
            maxValue: maxClimb
        }
    }

    Row {
        anchors.horizontalCenter: parent.horizontalCenter

        Column {
            width: root.width * 0.2
            height: 1
            anchors.verticalCenter: parent.verticalCenter
        }

        Compass {
            id: compass
            width: root.width * 0.6
            anchors.verticalCenter: parent.verticalCenter
            scalesColor: compassAvalible ? palette.textColor : palette.disabledColor
            courseColor: snsColor
        }

        Column {
            width: root.width * 0.2
            anchors.bottom: parent.bottom

            BatteryIndicator {
                id: battery
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: voltage.toFixed(2) + " " + qsTr("v")
                font.pixelSize: labelFontSize
                font.bold: true
            }

            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: current.toFixed(2) + " " + qsTr("A")
                font.pixelSize: labelFontSize
                font.bold: true
            }
        }
    }
}
