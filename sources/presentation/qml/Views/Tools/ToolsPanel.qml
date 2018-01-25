import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

ColumnLayout {
    id: root

    spacing: sizings.spacing

    Controls.Button {
        id: maxMinButton
        tipText: cornerVisible ? qsTr("Hide window") : qsTr("Show window")
        iconSource: cornerVisible ? "qrc:/icons/hide_window.svg" :
                                    "qrc:/icons/show_window.svg"
        onClicked: cornerVisible = !cornerVisible
    }

    Item {
        Layout.fillHeight: true
    }

    Controls.Button {
        iconSource: "qrc:/ui/plus.svg"
        tipText: qsTr("Zoom in")
        visible: map.visible
        autoRepeat: true
        onClicked: map.zoomLevel++
    }

    Controls.Button {
        iconSource: "qrc:/ui/minus.svg"
        tipText: qsTr("Zoom out")
        visible: map.visible
        autoRepeat: true
        onClicked: map.zoomLevel--
    }

    Controls.Button {
        tipText: qsTr("North")
        iconSource: "qrc:/icons/compas.svg"
        onClicked: bearingAnimation.start()
        enabled: map.trackingVehicleId === 0
        visible: map.visible

        RotationAnimation {
            id: bearingAnimation
            target: map
            properties: "bearing"
            to: 0
            duration: 200
            direction: RotationAnimation.Shortest
        }
    }

    Controls.Button {
        iconSource: "qrc:/icons/center.svg"
        tipText: qsTr("Center vehicle on map")
        checkable: true
        enabled: dashboard.selectedVehicle !== undefined && map.visible
        visible: map.visible
        onEnabledChanged: if (!enabled) checked = false;
        onCheckedChanged: map.trackingVehicleId = checked ?
                              dashboard.selectedVehicle.id : 0
    }
}
