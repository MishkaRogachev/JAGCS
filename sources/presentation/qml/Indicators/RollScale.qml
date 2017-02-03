import QtQuick 2.6
import "qrc:/JS/helper.js" as Helper

Item {
    id: rollScale

    property int roll: 0
    property int minRoll: -25
    property int maxRoll: 25
    property int rollStep: 5
    property color scaleColor: palette.textColor
    property int fontPixelSize: palette.fontPixelSize

    onRollChanged: canvas.requestPaint()
    onScaleColorChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.fill: parent
        onPaint: {
            var ctx = canvas.getContext('2d');

            ctx.clearRect(0, 0, width, height);

            ctx.lineWidth = 2;
            ctx.strokeStyle = scaleColor;
            ctx.fillStyle = scaleColor;
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
                ctx.lineTo(0, -height / 2 + palette.controlBaseSize / 6);
                ctx.restore();
            }

            ctx.stroke();
            ctx.beginPath();

            ctx.save();
            var rotation = Math.max(Math.min(-roll, maxRoll), minRoll);
            ctx.rotate(rotation * Math.PI / 180);

            ctx.moveTo(-palette.controlBaseSize / 4,
                       -height / 2 + palette.controlBaseSize / 4);
            ctx.lineTo(0, -height / 2);
            ctx.lineTo(palette.controlBaseSize / 4,
                       -height / 2 + palette.controlBaseSize / 4);

            ctx.font = 'bold ' + fontPixelSize + 'px sans-serif';
            ctx.fillText(Math.abs(roll), 0, -height / 2 +
                         palette.controlBaseSize / 1.5);

            ctx.restore();

            ctx.stroke();
            ctx.restore();
        }
    }
}
