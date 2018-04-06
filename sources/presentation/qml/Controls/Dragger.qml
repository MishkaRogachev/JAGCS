import QtQuick 2.6

import "../Shaders" as Shaders

Item {
    id: control

    property bool highlighted: dragEnabled
    readonly property bool dragActive: area.drag.active
    property real savedY : 0
    property int maxY: 0

    property alias dragEnabled: area.enabled

    function cancel() {
       y = savedY;
    }

    signal dragged()
    signal dropped()

    Drag.active: area.drag.active
    Drag.hotSpot.x: width / 2
    Drag.hotSpot.y: height / 2

    Shaders.Hatch {
        anchors.fill: parent
        color: customPalette.highlightColor
        visible: highlighted
        z: 10
    }

    MouseArea {
        id: area
        anchors.fill: control
        hoverEnabled: true
        drag.target: control
        drag.minimumY: 0
        drag.maximumY: maxY//drop.height// - control.height
        drag.axis: Drag.YAxis
        z: 10
        onPressed: savedY = control.y
        onReleased: if (drag.active) dropped()
        onPositionChanged: if (drag.active) dragged()
    }
}
