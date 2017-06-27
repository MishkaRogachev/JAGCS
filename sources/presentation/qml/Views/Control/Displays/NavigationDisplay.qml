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
    property real windDirection: 0
    property real windSpeed: 0

    implicitHeight: hsi.height

    Indicators.FdLabel { // TODO: icon
        anchors.top: parent.top
        anchors.left: parent.left
        prefix: qsTr("DIST")
        color: palette.activeMissionColor
        value: targetDistance
        width: parent.width * 0.2
    }

    Indicators.FdLabel { // TODO: icon
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        prefix: qsTr("HOME")
        value: homeDistance
        width: parent.width * 0.2
    }

    Indicators.WindIndicator { // TODO: icon
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
    }

    Indicators.FdLabel { // TODO: icon
        anchors.top: parent.top
        anchors.right: parent.right
        prefix: qsTr("TRG")
        color: palette.activeMissionColor
        value: targetBearing
        width: parent.width * 0.2
    }

    Indicators.FdLabel { // TODO: icon
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        prefix: qsTr("HDG")
        value: heading
        width: parent.width * 0.2
    }

    Indicators.FdLabel { // TODO: icon
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        prefix: qsTr("CRS")
        value: course
        width: parent.width * 0.2
    }
}
