import QtQuick 2.6
import "qrc:/JS/helper.js" as Helper

Item {
    id: rollScale

    property int roll: 0
    property int minRoll: -25
    property int maxRoll: 25
    property int rollStep: 5
    property color color: palette.textColor
    property int fontPixelSize: height > 0 ? height * 0.1 : 1

    onRollChanged: canvas.requestPaint()
    onColorChanged: canvas.requestPaint()
    onWidthChanged: canvas.requestPaint()
    onHeightChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.fill: parent
        onPaint: {
            var ctx = canvas.getContext('2d');

            ctx.clearRect(0, 0, width, height);

            ctx.lineWidth = 3;
            ctx.strokeStyle = color;
            ctx.fillStyle = color;
            ctx.textBaseline = 'middle';
            ctx.textAlign = 'center';

            ctx.save();
            ctx.beginPath();

            ctx.translate(width / 2, height / 2);
            for (var i = minRoll - (minRoll % rollStep); i <= maxRoll;
                 i += rollStep) {
                ctx.save();
                ctx.rotate(i * Math.PI / 180);
                ctx.moveTo(0, -height / 2);
                ctx.lineTo(0, -height / 2 + fontPixelSize / 4);
                ctx.restore();
            }

            ctx.stroke();
            ctx.beginPath();

            ctx.save();
            var rotation = Math.max(Math.min(-roll, maxRoll), minRoll);
            ctx.rotate(rotation * Math.PI / 180);

            ctx.moveTo(-fontPixelSize / 2,
                       -height / 2 + fontPixelSize / 2);
            ctx.lineTo(0, 2 - height / 2);
            ctx.lineTo(fontPixelSize / 2,
                       -height / 2 + fontPixelSize / 2);

            ctx.font = 'bold ' + fontPixelSize + 'px "Open Sans"';
            ctx.fillText(Math.abs(roll), 0, -height / 2 + fontPixelSize);

            ctx.restore();

            ctx.stroke();
            ctx.restore();
        }
    }
}
