import QtQuick 2.6
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import Industrial.Indicators 1.0 as Indicators

import "qrc:/Views/Common"

PointView  {
    id: item

    property bool dragEnabled: false
    property bool dragActive: false

    signal clicked()
    signal holded()
    signal dragged(real dx, real dy)
    signal dropped(real dx, real dy)

    width: dragEnabled && area.pressed ? area.width : implicitWidth
    height: dragEnabled && area.pressed ? area.height : implicitHeight

    Behavior on width { PropertyAnimation { duration: 100 } }
    Behavior on height { PropertyAnimation { duration: 100 } }

    MouseArea {
        id: area
        anchors.centerIn: parent
        width: industrial.baseSize * 1.2
        height: width
        preventStealing: true
        drag.target: dragEnabled ? picker : undefined
        drag.axis: Drag.XAndYAxis
        onPressed: dragActive = Qt.binding(function() {
            return Math.abs(picker.x) + Math.abs(picker.y) > industrial.baseSize * 0.1; })
        onClicked: item.clicked()
        onPressAndHold: {
            item.holded();

            dragActive = false;
            picker.x = 0;
            picker.y = 0;
        }
        onReleased: {
            if (!dragActive) return;

            item.dropped(picker.x, picker.y);

            dragActive = false;
            picker.x = 0;
            picker.y = 0;
        }
    }

    Controls.ColoredIcon {
        id: picker
        width: parent.width
        height: parent.height
        source: "qrc:/icons/aim.svg";
        color: Indicators.Theme.activeColor
        visible: dragActive
        onXChanged: item.dragged(x, y)
        onYChanged: item.dragged(x, y)
    }
}


