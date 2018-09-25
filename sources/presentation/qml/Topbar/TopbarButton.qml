import QtQuick 2.6
import JAGCS 1.0

Rectangle {
    id: button

    property alias clickEnabled: area.enabled

    signal clicked()

    implicitWidth: controlSize.baseSize * 0.75
    implicitHeight: controlSize.baseSize * 0.75
    radius: 1
    color: area.pressed ? customPalette.highlightColor : "transparent"

    Rectangle {
        anchors.fill: parent
        color: customPalette.textColor
        radius: parent.radius
        opacity: 0.1
        visible: area.containsMouse && clickEnabled
    }

    MouseArea {
        id: area
        anchors.fill: parent
        anchors.bottomMargin: -controlSize.baseSize * 0.25
        hoverEnabled: true
        onClicked: button.clicked()
    }
}


