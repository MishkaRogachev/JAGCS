import QtQuick 2.6

Rectangle {
    id: root

    property bool operational: true
    property real yaw: 0
    property real size: width * 0.07

    Behavior on yaw { RotationAnimation { duration: 100; direction: RotationAnimation.Shortest } }

    implicitHeight: width
    radius: Math.min(width / 2, height / 2)
    opacity: enabled ? 1 : 0.33

    onOperationalChanged: canvas.requestPaint()
    onWidthChanged: canvas.requestPaint()
    onHeightChanged: canvas.requestPaint()
    color: customPalette.backgroundColor

    Canvas {
        id: canvas
        anchors.fill: parent
        rotation: yaw
        onPaint: {
            var ctx = canvas.getContext('2d');

            ctx.clearRect(0, 0, width, height);

            ctx.save();

            ctx.fillStyle = operational ? customPalette.textColor : customPalette.dangerColor;

            ctx.translate(width / 2, 0);

            ctx.beginPath();
            ctx.moveTo(0, 0);
            ctx.lineTo(size, size);
            ctx.lineTo(-size, size);
            ctx.closePath();
            ctx.fill();

            ctx.restore();
        }
    }
}
