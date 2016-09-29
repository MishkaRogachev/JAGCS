import QtQuick 2.6
import "qrc:/JS/helper.js" as Helper

Item {
    id: pitchScale

    property int pitch: 0
    property int roll: 0
    property int minPitch: -25
    property int maxPitch: 25
    property int valueStep: 10

    width: 96
    onPitchChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.fill: parent
        rotation: -roll
        onPaint: {
            var ctx = canvas.getContext('2d');

            ctx.clearRect(0, 0, width, height);

            ctx.lineWidth = 2;
            ctx.strokeStyle = '#ecf0f1' // TODO: palette
            ctx.fillStyle = '#ecf0f1' // TODO: palette
            ctx.font = '11pt Open Sans';
            ctx.textBaseline = 'middle';

            ctx.save();
            ctx.beginPath();

            var counter = 0;
            for (var i = minPitch - (minPitch % valueStep); i <= maxPitch;
                 i += (valueStep / 2)) {
                var major = (counter++ % 2) == 0;
                var yPos = height - Helper.mapToRange(i, minPitch, maxPitch, height);

                ctx.moveTo(major ? 24 : 36, yPos);
                ctx.lineTo(major ? width - 24 : width - 36, yPos);

                if (major) {
                    ctx.textAlign = 'right';
                    ctx.fillText(i, 22, yPos + 2);
                    ctx.textAlign = 'left';
                    ctx.fillText(i, width - 22, yPos + 2);
                }
            }
            ctx.stroke();
            ctx.restore();
        }
    }
}
