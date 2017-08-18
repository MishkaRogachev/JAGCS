import QtQuick 2.6
import "qrc:/JS/helper.js" as Helper

Item {
    id: planeMark

    property int pitch: 0
    property int roll: 0
    property int effectiveHeight: height

    property color markColor
    property int markWidth: 4

    onRollChanged: canvas.requestPaint()
    onPitchChanged: canvas.requestPaint()
    onMarkColorChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.fill: parent
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
            ctx.rotate(-roll * Math.PI / 180);
            ctx.translate(0, offset - effectiveHeight / 2);

            ctx.moveTo(-width / 3, 0);
            ctx.lineTo(-width / 6, 0);
            ctx.lineTo(-width / 12, width / 12);
            ctx.lineTo(0, 0);
            ctx.lineTo(width / 12, width / 12);
            ctx.lineTo(width / 6, 0);
            ctx.lineTo(width / 3, 0);

            ctx.moveTo(0, 0);
            ctx.arc(0, 0, markWidth, 0, 2 * Math.PI, false);

            ctx.stroke();
            ctx.restore();
        }
    }
}
