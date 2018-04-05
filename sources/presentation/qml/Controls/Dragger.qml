import QtQuick 2.6

import "../Shaders" as Shaders

Item {
    id: control

    property alias dragEnabled: area.enabled

    signal dropped()

    Drag.active: area.drag.active
    Drag.hotSpot.x: width / 2
    Drag.hotSpot.y: height / 2

    MouseArea {
        id: area
        anchors.fill: control
        hoverEnabled: true
        drag.target: control
        drag.minimumY: 0
        drag.maximumY: control.parent.height - control.height
        drag.axis: Drag.YAxis
        drag.smoothed: false
        z: 10
        onReleased: if (drag.active) dropped()
    }
}
