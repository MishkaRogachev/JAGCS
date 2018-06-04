import QtQuick 2.6
import JAGCS 1.0

Rectangle {
    id: button

    signal clicked()

    implicitWidth: sizings.controlBaseSize * 0.75
    implicitHeight: sizings.controlBaseSize * 0.75
    radius: 1
    color: area.pressed ? customPalette.highlightColor : "transparent"

    Rectangle {
        anchors.fill: parent
        color: customPalette.textColor
        radius: parent.radius
        opacity: 0.1
        visible: area.containsMouse
    }

    MouseArea {
        id: area
        anchors.fill: parent
        anchors.bottomMargin: -sizings.controlBaseSize * 0.25
        hoverEnabled: true
        onClicked: button.clicked()
    }
}


