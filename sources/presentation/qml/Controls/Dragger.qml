import QtQuick 2.6

import "../Shaders" as Shaders

Item {
    id: control

    property alias dragEnabled: area.enabled

    Drag.active: area.drag.active
    Drag.hotSpot.x: width / 2
    Drag.hotSpot.y: height / 2

    Shaders.Hatch {
        anchors.fill: parent
        color: area.drag.active ? customPalette.highlightColor : customPalette.selectionColor
        visible: dragEnabled
        z: 10
    }

    MouseArea {
        id: area
        anchors.fill: control
        hoverEnabled: true
        drag.target: control
        drag.minimumX: 0
        drag.minimumY: 0
        drag.maximumX: control.parent.width - control.width
        drag.maximumY: control.parent.height - control.height
        z: 10
    }
}
