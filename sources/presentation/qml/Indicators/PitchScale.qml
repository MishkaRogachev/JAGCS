import QtQuick 2.6
import "qrc:/JS/helper.js" as Helper

Item {
    id: pitchScale

    property int roll: 0
    property int minPitch: -25
    property int maxPitch: 25
    property int pitchStep: 10
    property color color: palette.textColor
    property int fontPixelSize: width * 0.06

    onMinPitchChanged: canvas.requestPaint()
    onMaxPitchChanged: canvas.requestPaint()
    onColorChanged: canvas.requestPaint()
    onWidthChanged: canvas.requestPaint()
    onHeightChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.fill: parent
        rotation: -roll
        onPaint: {
            var ctx = canvas.getContext('2d');

            ctx.clearRect(0, 0, width, height);

            ctx.lineWidth = 2;
            ctx.strokeStyle = color;
            ctx.fillStyle = color;
            ctx.font = 'bold ' + fontPixelSize + 'px "Open Sans"';
            ctx.textBaseline = 'middle';

            ctx.save();
            ctx.beginPath();

            var counter = 0;
            for (var pitch = minPitch - (minPitch % pitchStep); pitch <= maxPitch;
                 pitch += (pitchStep / 2)) {
                var major = (counter++ % 2) == 0;
                if (pitch == 0) continue;

                var yPos = height - Helper.mapToRange(pitch, minPitch, maxPitch, height);

                ctx.save();
                ctx.translate(width / 2, yPos);

                var tickLength = major ? Math.min(width / 14 + Math.abs(pitch) * 2, width / 4) :
                                         width / 16
                ctx.moveTo(-tickLength, 0);
                ctx.lineTo(+tickLength, 0);

                if (major) {
                    ctx.textAlign = 'left';
                    ctx.fillText(pitch, tickLength + 2, 2);
                    ctx.textAlign = 'right';
                    ctx.fillText(pitch, -tickLength - 2, 2);
                }

                ctx.restore();
            }
            ctx.stroke();
            ctx.restore();
        }
    }
}
