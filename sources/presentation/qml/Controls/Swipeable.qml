import QtQuick 2.6

Item {
    id: control

    property int widthOfSeizure: palette.controlBaseSize * 0.5
    property int dragStartX: 0

    property bool swipeToRight: false
    property bool isOpened: swipeToRight ? (dragStartX - width / 2 > x) :
                                           (dragStartX + x > width / 2)

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

    MouseArea {
        id: dragArea
        anchors.fill: parent

        drag.target: parent
        drag.axis: Drag.XAxis
        drag.minimumX: swipeToRight ? dragStartX - width + widthOfSeizure : dragStartX
        drag.maximumX: swipeToRight ? dragStartX : dragStartX + width - widthOfSeizure

        onReleased: control.isOpened ? control.open() : control.close()
    }
}
