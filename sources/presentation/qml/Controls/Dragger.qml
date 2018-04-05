import QtQuick 2.6

import "../Shaders" as Shaders

Item {
    id: control

    property alias dragEnabled: area.enabled
    property real savedY : 0

    function cancel() {
       y = savedY;
    }

    signal dragged()
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
        z: 10
        onPressed: savedY = control.y
        onReleased: if (drag.active) dropped()
        onPositionChanged: if (drag.active) dragged()
    }
}
