import QtQuick 2.6

import "../Controls"

Column {
    id: root

    property alias armed: horizont.armed
    property alias insAvalible: horizont.insAvalible
    property alias pitch: horizont.pitch
    property alias roll: horizont.roll
    property alias indicatedAirSpeed: horizont.velocity
    property alias altitude: horizont.altitude
    property alias terrainAltitude: horizont.terrainAltitude
    property alias rollInverted: horizont.rollInverted
    property alias barometerAvalible: horizont.altitudeAvalible
    property alias airSpeedAvalible: horizont.velocityAvalible

    property bool compassAvalible: true
    property alias heading: compass.heading
    property alias course: compass.course
    property alias windDirection: compass.windDirection
    property alias homeDirection: compass.homeDirection

    property real missionDistance: 0.0
    property real homeDistance: 0.0

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

    property int throttle: 0
    property int minThrottle: 0
    property int maxThrottle: 100

    property bool rangeFinderAvalible: false
    property int geometricAltitude: 0

    property int labelFontSize: palette.fontPixelSize * 0.8

    spacing: 10

    Behavior on climb { PropertyAnimation { duration: 100 } }
    Behavior on heading { PropertyAnimation { duration: 100 } }

    Row {
        anchors.horizontalCenter: parent.horizontalCenter

        BarIndicator {
            id: throttleScale
            anchors.verticalCenter: parent.verticalCenter
            width: root.width * 0.03
            height: horizont.height * 0.8
            value: throttle
            fillColor: palette.selectionColor
            minValue: minThrottle
            maxValue: maxThrottle
            z: 1
        }

        ArtificialHorizont {
            id: horizont
            anchors.verticalCenter: parent.verticalCenter
            width: root.width * 0.94
            height: width
            velocityPrefix: qsTr("IAS, m/s")
            altitudePrefix: qsTr("Hbar, m")

            FdLabel {
                anchors.top: parent.top
                anchors.topMargin: -height / 4
                anchors.left: parent.left
                prefix: qsTr("GS, m/s")
                value: groundSpeed
                width: parent.width * 0.2
                color: snsColor
            }

            Column {
                anchors.top: parent.bottom
                anchors.topMargin: palette.spacing - tasLabel.height
                anchors.left: parent.left
                width: parent.width * 0.2
                spacing: palette.spacing

                FdLabel {
                    id: tasLabel
                    prefix: qsTr("TAS, m/s")
                    value: trueAirSpeed
                    digits: 1
                    available: airSpeedAvalible
                    width: parent.width
                }

                ColoredIcon {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width / 2
                    height: width
                    source: "qrc:/icons/wind.svg"
                    color: homeLabel.color
                }

                FdLabel {
                    value: windSpeed
                    digits: 1
                    suffix: qsTr("m/s")
                    available: airSpeedAvalible
                    width: parent.width
                }

                ColoredIcon {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width / 2
                    height: width
                    source: "qrc:/icons/home.svg"
                    color: homeLabel.color
                }

                FdLabel {
                    id: homeLabel
                    value: homeDistance > 1000 ?
                               homeDistance / 1000 : homeDistance
                    digits: homeDistance > 1000 ? 1 : 0
                    suffix: homeDistance > 1000 ? qsTr("km") : qsTr("m")
                    available: homeDistance > -1
                    width: parent.width
                }

                Rectangle {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width / 3
                    height: width
                    radius: width / 2
                    color: missionDistance > -1 ?
                               palette.raisedColor : palette.sunkenColor
                    border.color: missionDistance > -1 ?
                                      palette.selectionColor : palette.disabledColor
                    border.width: 2
                }

                FdLabel {
                    value: missionDistance > 1000 ?
                               missionDistance / 1000 : missionDistance
                    digits: missionDistance > 1000 ? 1 : 0
                    suffix: missionDistance > 1000 ? qsTr("km") : qsTr("m")
                    available: missionDistance > -1
                    width: parent.width
                }
            }

            FdLabel {
                anchors.top: parent.top
                anchors.topMargin: -height / 4
                anchors.right: parent.right
                prefix: qsTr("Hsns, m")
                value: snsAltitude
                width: parent.width * 0.2
                color: snsColor
            }

            Column {
                anchors.top: parent.bottom
                anchors.topMargin: palette.spacing - hGeoLabel.height
                anchors.right: parent.right
                width: parent.width * 0.2
                spacing: palette.spacing

                FdLabel {
                    id: hGeoLabel
                    prefix: qsTr("Hgeo, m")
                    value: geometricAltitude
                    width: parent.width
                    available: rangeFinderAvalible
                }

                BatteryIndicator {
                    id: battery
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width / 2
                    height: width
                }

                FdLabel {
                    width: parent.width
                    suffix: qsTr("V")
                    value: voltage
                    digits: 2
                    available: voltage > -1
                }

                ColoredIcon {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width / 2
                    height: width
                    source: "qrc:/icons/current.svg"
                    color: homeLabel.color
                }

                FdLabel {
                    width: parent.width
                    suffix: qsTr("A")
                    value: current
                    digits: 2
                    available: current > -1
                }
            }
        }

        BarIndicator {
            id: climbScale
            anchors.verticalCenter: parent.verticalCenter
            width: root.width * 0.03
            height: horizont.height * 0.8
            value: climb
            fillColor: {
                if (!barometerAvalible) return palette.disabledColor;
                if (value > 0) return palette.skyColor;
                if (value > minValue) return palette.groundColor;
                return palette.negativeColor;
            }
            minValue: minClimb
            maxValue: maxClimb
        }
    }

    Compass {
        id: compass
        width: horizont.width * 0.6
        anchors.horizontalCenter: parent.horizontalCenter
        scalesColor: compassAvalible ? palette.textColor : palette.disabledColor
        courseColor: snsColor
    }
}
