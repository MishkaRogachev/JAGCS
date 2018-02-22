import QtQuick 2.6
import "qrc:/JS/helper.js" as Helper

Ladder {
    id: root

    property bool inputEnabled: false
    property real inputMin: 0
    property real inputMax: 1
    property real inputValue: 0

    signal picked(real value)

    Rectangle {
        width: root.width / 2
        height: 2
        x: root.mirrored ? width : 0
        y: root.height - Helper.mapToRange(inputValue, inputMin, inputMax,
                                           root.height - height) - height
        color: palette.selectionColor
        visible: inputEnabled
        z: -1
    }

    MouseArea {
        anchors.fill: root
        onMouseYChanged: root.picked(Helper.mapFromRange(
                                         Math.max(0, Math.min(root.height, root.height - mouseY)),
                                         inputMin, inputMax, root.height))
    }
}
