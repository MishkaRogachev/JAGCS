import QtQuick 2.6

import "qrc:/Controls" as Controls

Item {
    id: control

    property alias name: content.text

    clip: true
    implicitWidth: sizings.controlBaseSize * 3
    implicitHeight: sizings.controlBaseSize

    Controls.ContentItem {
        id: content
        anchors.fill: parent
        text: selectedVehicle !== undefined ? selectedVehicle.name : qsTr("No vehicle")
        iconSource: translator.imageFromVehicleState(vehicle.vehicleState)
        font.bold: true
        font.pixelSize: sizings.fontPixelSize * 0.75
    }

    MouseArea {
        id: area
        height: parent.height
        width: height
        hoverEnabled: true
    }

    Controls.ToolTip {
        visible: area.containsMouse
        text: translator.translateVehicleState(vehicle.vehicleState)
        delay: 1000
    }
}
