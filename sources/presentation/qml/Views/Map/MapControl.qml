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
}
