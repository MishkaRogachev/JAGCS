import QtQuick 2.6
import "qrc:/JS/helper.js" as Helper

Item {
    id: planeMark

    property real pitch: 0.0
    property real roll: 0.0
    property real effectiveHeight: height

    property color markColor
    property real markWidth: 2

    implicitHeight: width
    onWidthChanged: canvas.requestPaint()
    onHeightChanged: canvas.requestPaint()
    onMarkColorChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.centerIn: parent
        anchors.verticalCenterOffset: effectiveHeight / 2 - Helper.mapToRange(
                                          -pitch, minPitch, maxPitch, effectiveHeight)
        width: parent.width
        height: parent.height
        rotation: -roll

        onPaint: {
            var ctx = canvas.getContext('2d');

            ctx.clearRect(0, 0, width, height);

            var offset = Helper.mapToRange(pitch, minPitch, maxPitch, effectiveHeight);

            ctx.lineWidth = markWidth;
            ctx.strokeStyle = markColor;
            ctx.fillStyle = markColor;

            ctx.save();
            ctx.beginPath();

            ctx.translate(width / 2, height / 2);

            ctx.moveTo(-width / 2, 0);
            ctx.lineTo(-width / 4, 0);
            ctx.lineTo(-width / 8, width / 8);
            ctx.lineTo(0, 0);
            ctx.lineTo(width / 8, width / 8);
            ctx.lineTo(width / 4, 0);
            ctx.lineTo(width / 2, 0);

            ctx.moveTo(0, 0);
            ctx.arc(0, 0, markWidth, 0, 2 * Math.PI, false);

            ctx.stroke();
            ctx.restore();
        }
    }
}
