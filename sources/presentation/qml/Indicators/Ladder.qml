import QtQuick 2.0
import "qrc:/JS/helper.js" as Helper

Item {
    id: root

    property alias value: label.value
    property int minValue: 0
    property int maxValue: 100
    property int valueStep: 20

    property int fontPixelSize: root.width * 0.2
    property int minorTickSize: fontPixelSize * 0.4
    property int majorTickSize: fontPixelSize * 0.6
    property int textOrigin: fontPixelSize * 0.8
    property int lineWidth: 2
    property alias canvasRotation: canvas.rotation

    property alias prefix: label.prefix
    property color color: palette.textColor

    property bool vertical: (canvasRotation >= 90 && canvasRotation < 180) ||
                            (canvasRotation <= -90 && canvasRotation > -180)

    clip: true
    onValueChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.centerIn: parent
        width: vertical ? parent.height : parent.width
        height: vertical ? parent.width : parent.height
        onPaint: {
            var ctx = canvas.getContext('2d');

            ctx.clearRect(0, 0, width, height);

            ctx.lineWidth = lineWidth;
            ctx.strokeStyle = color;
            ctx.fillStyle = color;
            ctx.font = 'bold ' + fontPixelSize + 'px "Open Sans"';
            ctx.textAlign = vertical ? (canvasRotation > 0 ? 'right' : 'left') : 'center';
            ctx.textBaseline = vertical ? 'middle' : 'top';
            
            ctx.save();
            ctx.translate(0, lineWidth);

            ctx.beginPath();
            ctx.moveTo(0, 0);
            ctx.lineTo(width, 0);

            ctx.moveTo(lineWidth / 2, 0);
            ctx.lineTo(lineWidth / 2, majorTickSize);
            ctx.moveTo(width - lineWidth / 2, 0);
            ctx.lineTo(width - lineWidth / 2, majorTickSize);

            var counter = 0;
            for (var i = minValue - (minValue % valueStep); i <= maxValue;
                 i += (valueStep / 2)) {

                var major = (counter++ % 2) == 0;
                var xPos = canvasRotation > 0 ?
                            width - Helper.mapToRange(i, minValue, maxValue, width) :
                            Helper.mapToRange(i, minValue, maxValue, width);
                ctx.moveTo(xPos, 0);
                ctx.lineTo(xPos, major ? majorTickSize : minorTickSize);
                if (major) {
                    ctx.save();
                    ctx.translate(xPos, textOrigin);
                    ctx.rotate(-canvasRotation * Math.PI / 180);
                    ctx.fillText(i, 0, lineWidth);
                    ctx.restore();
                }
            }
            ctx.stroke();
            ctx.restore();
        }
    }

    FdLabel {
        id: label
        anchors.centerIn: parent
        width: canvas.height
        color: root.color
    }
}
