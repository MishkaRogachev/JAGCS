import QtQuick 2.6

import "../Controls" as Controls

Item {
    id: root

    property alias heading: hsi.heading
    property alias course: hsi.course
    property alias targetBearing: hsi.targetBearing
    property alias trackError: hsi.trackError

    property int targetDistance: 0
    property int homeDistance: 0
    property int waypoint: 0

    implicitHeight: hsi.height

    FdLabel { // TODO: icon
        anchors.top: parent.top
        anchors.left: parent.left
        prefix: qsTr("DIST")
        value: targetDistance
        width: parent.width * 0.2
    }

    FdLabel { // TODO: icon
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        prefix: qsTr("HOME")
        value: homeDistance
        width: parent.width * 0.2
    }

    FdLabel { // TODO: icon
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        prefix: qsTr("WP")
        value: waypoint
        width: parent.width * 0.2
    }

    SituationIndicator {
        id: hsi
        anchors.centerIn: parent
        width: parent.width * 0.6
    }

    FdLabel { // TODO: icon
        anchors.top: parent.top
        anchors.right: parent.right
        prefix: qsTr("TRG")
        digits: 2
        value: targetBearing
        width: parent.width * 0.2
    }

    FdLabel { // TODO: icon
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        prefix: qsTr("HDG")
        digits: 2
        value: heading
        width: parent.width * 0.2
    }

    FdLabel { // TODO: icon
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        prefix: qsTr("CRS")
        digits: 2
        value: course
        width: parent.width * 0.2
    }
}
