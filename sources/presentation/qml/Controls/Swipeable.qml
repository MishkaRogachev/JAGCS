import QtQuick 2.6

Item {
    id: control

    property int widthOfSeizure: sizings.controlBaseSize * 0.5
    property int dragStartX: 0
    property real dragAccFactor: 0.1

    property bool swipeToRight: false
    property bool isOpened: swipeToRight ? x == dragArea.drag.minimumX :
                                           x == dragArea.drag.maximumX

    function close() {
        x = Qt.binding(swipeToRight ? function() { return dragArea.drag.maximumX; } :
                                      function() { return dragArea.drag.minimumX; });
    }

    function open() {
        x = Qt.binding(swipeToRight ? function() { return dragArea.drag.minimumX; } :
                                      function() { return dragArea.drag.maximumX; });
    }

    x: dragStartX
    Drag.active: dragArea.drag.active

    // TODO: try MultiPointTouchArea
    MouseArea {
        id: dragArea

        property int lastX: 0

        anchors.fill: parent
        anchors.rightMargin: swipeToRight ? 0 : -widthOfSeizure
        anchors.leftMargin: swipeToRight ? -widthOfSeizure : 0
        drag.target: parent
        drag.axis: Drag.XAxis
        drag.minimumX: swipeToRight ? dragStartX - parent.width : dragStartX
        drag.maximumX: swipeToRight ? dragStartX : dragStartX + parent.width

        onPressed: lastX = parent.x
        onReleased: {
            if (parent.x < lastX) {
                lastX - parent.x > width * dragAccFactor ? control.open() : control.close();
            }
            else {
                parent.x - lastX > width * dragAccFactor ? control.close() : control.open();
            }
        }
    }

    Rectangle {
        color: palette.highlightColor
        opacity: dragArea.pressed ? 0.5 : 0.0
        anchors.fill: dragArea

        Behavior on opacity { PropertyAnimation { duration: 200 } }
    }
}
