import QtQuick 2.0
import "qrc:/JS/helper.js" as Helper

Item {
    id: scale

    property int value: 0
    property int minValue: 0
    property int maxValue: 100
    property int valueStep: 20
    property alias canvasRotation: canvas.rotation

    property bool vertical: (canvasRotation >= 90 && canvasRotation < 180) ||
                            (canvasRotation <= -90 && canvasRotation > -180)

    width: 64
    height: 64
    onValueChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.centerIn: parent
        width: vertical ? parent.height : parent.width
        height: vertical ? parent.width : parent.height
        onPaint: {
            var ctx = canvas.getContext('2d');

            ctx.clearRect(0, 0, width, height);

            ctx.lineWidth = 2;
            ctx.strokeStyle = Qt.white // TODO: palette
            ctx.fillStyle = Qt.white // TODO: palette
            ctx.font = '11pt Open Sans';
            ctx.textAlign = vertical ?
                        (canvasRotation > 0 ? 'right' : 'left') : 'center';
            ctx.textBaseline = vertical ? 'middle' : 'top';

            ctx.save();
            ctx.beginPath();
            ctx.moveTo(0, 2);
            ctx.lineTo(width, 2);

            var counter = 0;
            for (var i = minValue - (minValue % valueStep); i <= maxValue;
                 i += (valueStep / 2)) {
                var major = (counter++ % 2) == 0;
                var xPos = canvasRotation > 0 ?
                            width - Helper.mapToRange(i, minValue, maxValue, width) :
                            Helper.mapToRange(i, minValue, maxValue, width);
                ctx.moveTo(xPos, 2);
                ctx.lineTo(xPos, major ? 10 : 8);
                if (major) {
                    ctx.save();
                    ctx.translate(xPos, 12);
                    ctx.rotate(-canvasRotation * Math.PI / 180);
                    ctx.fillText(i, 0, 2);
                    ctx.restore();
                }
            }

            ctx.stroke();
            ctx.clearRect(width / 2 - 16, 3, 32, 64);

            ctx.beginPath();
            ctx.moveTo(width / 2 - 16, 16);
            ctx.lineTo(width / 2, 4);
            ctx.lineTo(width / 2 + 16, 16);
            ctx.stroke();

            ctx.font = '14pt Open Sans';
            ctx.textAlign = vertical ?
                        (canvasRotation < 0 ? 'left' :'right') : 'center';
            ctx.textBaseline = vertical ? 'middle' : 'top';
            ctx.save();
            ctx.translate(width / 2, 16);
            ctx.rotate(-canvasRotation * Math.PI / 180);
            ctx.fillText(value, 0, 2);
            ctx.restore();
            ctx.restore();
        }
    }
}
