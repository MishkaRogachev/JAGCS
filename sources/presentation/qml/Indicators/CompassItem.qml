import QtQuick 2.6

import "../Controls"

Item {
    id: root

    property alias iconSource: icon.source

    Rectangle {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        width: root.width / 6
        height: width
        color: palette.backgroundColor
        border.color: palette.missionColor
        border.width: 2
        radius: width / 2
        rotation: -root.rotation

        ColoredIcon {
            id: icon
            anchors.centerIn: parent
            width: parent.width * 0.8
            height: parent.height * 0.8
            color: palette.textColor
        }
    }
}
