import QtQuick 2.6
import "qrc:/JS/helper.js" as Helper

Item {
    id: pitchScale

    property int pitch: 0
    property int roll: 0
    property int minPitch: -25
    property int maxPitch: 25
    property int pitchStep: 10
    property int fontPixelSize: palette.fontPixelSize

    width: palette.controlBaseSize * 3
    onPitchChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.fill: parent
        rotation: -roll
        onPaint: {
            var ctx = canvas.getContext('2d');

            ctx.clearRect(0, 0, width, height);

            ctx.lineWidth = 2;
            ctx.strokeStyle = palette.textColor;
            ctx.fillStyle = palette.textColor;
            ctx.font = fontPixelSize + 'px sans-serif';
            ctx.textBaseline = 'middle';

            ctx.save();
            ctx.beginPath();

            var counter = 0;
            for (var i = minPitch - (minPitch % pitchStep); i <= maxPitch;
                 i += (pitchStep / 2)) {
                var major = (counter++ % 2) == 0;
                if (i == 0) continue;

                var yPos = height - Helper.mapToRange(i, minPitch, maxPitch, height);

                ctx.save();

                ctx.translate(width / 2, yPos);
                ctx.moveTo(major ? -width / 4 : -width / 6, 0);
                ctx.lineTo(major ? width / 4 : width / 6, 0);

                if (major) {
                    ctx.textAlign = 'right';
                    ctx.fillText(i, width / 2, 2);
                    ctx.textAlign = 'left';
                    ctx.fillText(i, -width / 2, 2);
                }

                ctx.restore();
            }
            ctx.stroke();
            ctx.restore();
        }
    }
}
