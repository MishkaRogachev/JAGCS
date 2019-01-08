import QtQuick 2.6
import JAGCS 1.0

Rectangle {
    id: button

    property alias clickEnabled: area.enabled

    signal clicked()

    implicitWidth: industrial.baseSize * 0.75
    implicitHeight: industrial.baseSize * 0.75
    radius: 1
    color: area.pressed ? industrial.colors.highlight : "transparent"

    Rectangle {
        anchors.fill: parent
        color: industrial.colors.onSurface
        radius: parent.radius
        opacity: 0.1
        visible: area.containsMouse && clickEnabled
    }

    MouseArea {
        id: area
        anchors.fill: parent
        anchors.bottomMargin: -industrial.baseSize * 0.25
        hoverEnabled: true
        onClicked: button.clicked()
    }
}


