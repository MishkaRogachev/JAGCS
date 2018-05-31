import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "qrc:/Views/Common"

PointView  {
    id: item

    property bool dragEnabled: false

    signal clicked()
    signal holded()
    signal dragged(real dx, real dy)

    width: dragEnabled && area.pressed ? area.width : implicitWidth
    height: dragEnabled && area.pressed ? area.height : implicitHeight

    Behavior on width { PropertyAnimation { duration: 100 } }
    Behavior on height { PropertyAnimation { duration: 100 } }

    MouseArea {
        id: area
        anchors.centerIn: parent
        width: sizings.controlBaseSize * 1.2
        height: width
        preventStealing: true
        drag.target: dragEnabled ? picker : undefined
        drag.axis: Drag.XAndYAxis
        onClicked: item.clicked()
        onPressAndHold: item.holded()
        onReleased: {
            if (!drag.active) return;

            item.dragged(picker.x, picker.y);
            picker.x = 0;
            picker.y = 0;
        }
    }

    Controls.ColoredIcon {
        id: picker
        width: parent.width
        height: parent.height
        source: "qrc:/icons/aim.svg";
        color: customPalette.activeMissionColor
        visible: area.drag.active
    }
}


