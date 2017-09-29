import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

ColumnLayout {
    id: root

    RotationAnimation {
        id: bearingAnimation
        target: map
        properties: "bearing"
        to: 0
        duration: 200
        direction: RotationAnimation.Shortest
    }

    z: 10000

    Controls.Button {
        iconSource: "qrc:/icons/compas.svg"
        onClicked: bearingAnimation.start()
        enabled: !map.trackingVehicle
    }
}
