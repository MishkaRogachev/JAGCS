import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

ColumnLayout {
    id: root

    spacing: sizings.spacing

    RotationAnimation {
        id: bearingAnimation
        target: map
        properties: "bearing"
        to: 0
        duration: 200
        direction: RotationAnimation.Shortest
    }

    Controls.Button {
        tipText: qsTr("North")
        iconSource: "qrc:/icons/compas.svg"
        onClicked: bearingAnimation.start()
        enabled: map.trackingVehicleId === 0
    }

    Controls.Button {
        id: tracking
        iconSource: "qrc:/icons/center.svg"
        tipText: qsTr("Center vehicle on map")
        checkable: true
        enabled: dashboard.selectedVehicle !== undefined && map.visible
        onEnabledChanged: if (!enabled) checked = false;
        onCheckedChanged: map.trackingVehicleId = checked ?
                              dashboard.selectedVehicle.id : 0
    }

    Controls.Button {
        tipText: cornerMap ? qsTr("Map") : qsTr("Video")
        iconSource: cornerMap ? "qrc:/icons/map-marker.svg" : "qrc:/icons/video.svg"
        onClicked: cornerMap = !cornerMap
    }

    Controls.Button {
        id: maxMinButton
        tipText: cornerVisible ? qsTr("Hide window") : qsTr("Show window")
        iconSource: cornerVisible ? "qrc:/icons/window.svg" : "qrc:/icons/subwindow.svg"
        onClicked: cornerVisible = !cornerVisible
    }
}
