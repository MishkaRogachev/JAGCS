import QtQuick 2.6

import "qrc:/Indicators" as Indicators

Item {
    id: root

    property alias heading: hsi.heading
    property alias course: hsi.course
    property alias targetBearing: hsi.targetBearing
    property alias trackError: hsi.trackError

    property int targetDistance: 0
    property int homeDistance: 0
    property real homeDirection: 0
    property real windDirection: 0
    property real windSpeed: 0

    implicitHeight: hsi.height

    Indicators.DistanceLabel {
        anchors.top: parent.top
        anchors.left: parent.left
        prefix: qsTr("DIST")
        color: palette.activeMissionColor
        distance: targetDistance
        width: parent.width * 0.2
    }

    Indicators.DistanceLabel {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        prefix: qsTr("HOME")
        distance: homeDistance
        width: parent.width * 0.2
    }

    Indicators.WindIndicator {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width * 0.2
        direction: windDirection
        speed: windSpeed
    }

    Indicators.SituationIndicator {
        id: hsi
        anchors.centerIn: parent
        width: parent.width * 0.6

        Item {
            anchors.fill: parent
            rotation: homeDirection - heading
            visible: homeDistance > 0

            Image {
                width: parent.width * 0.12
                height: width
                anchors.centerIn: parent
                anchors.verticalCenterOffset: -parent.height * 0.3
                source: "qrc:/icons/home.svg"
                rotation: -parent.rotation
            }
        }
    }

    Indicators.FdLabel {
        anchors.top: parent.top
        anchors.right: parent.right
        prefix: qsTr("TRG")
        color: palette.activeMissionColor
        value: targetBearing
        width: parent.width * 0.2
    }

    Indicators.FdLabel {
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        prefix: qsTr("HDG")
        value: heading
        width: parent.width * 0.2
    }

    Indicators.FdLabel {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        prefix: qsTr("CRS")
        value: course
        width: parent.width * 0.2
    }
}
