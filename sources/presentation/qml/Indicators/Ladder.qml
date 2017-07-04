import QtQuick 2.0
import "qrc:/JS/helper.js" as Helper

Item {
    id: root

    property int value: 0
    property int minValue: 0
    property int maxValue: 100
    property int valueStep: 20

    property int fontPixelSize: root.width * 0.2
    property int minorTickSize: fontPixelSize * 0.4
    property int majorTickSize: fontPixelSize * 0.6
    property int textOrigin: fontPixelSize * 0.8
    property alias canvasRotation: canvas.rotation

    property bool operational: false
    property string prefix
    property color color: enabled ? (operational ? palette.textColor : palette.negativeColor) :
                                    palette.disabledColor
    property bool vertical: (canvasRotation >= 90 && canvasRotation < 180) ||
                            (canvasRotation <= -90 && canvasRotation > -180)

    clip: true
    onColorChanged: canvas.requestPaint()
    onValueChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.centerIn: parent
        width: vertical ? parent.height : parent.width
        height: vertical ? parent.width : parent.height
        onPaint: {
            var ctx = canvas.getContext('2d');

            ctx.clearRect(0, 0, width, height);

            ctx.strokeStyle = color;
            ctx.fillStyle = color;
            ctx.font = 'bold ' + fontPixelSize + 'px "Open Sans"';
            ctx.textAlign = vertical ? (canvasRotation > 0 ? 'right' : 'left') : 'center';
            ctx.textBaseline = vertical ? 'middle' : 'top';
            
            ctx.save();
            ctx.translate(0, 2);
            ctx.lineWidth = 2;
            ctx.beginPath();
            ctx.moveTo(0, 0);
            ctx.lineTo(width, 0);

            ctx.moveTo(1, 0);
            ctx.lineTo(1, majorTickSize);
            ctx.moveTo(width - 1, 0);
            ctx.lineTo(width - 1, majorTickSize);
            ctx.stroke();

            var counter = 0;
            for (var i = minValue - (minValue % valueStep); i <= maxValue;
                 i += (valueStep / 2)) {

                var major = (counter++ % 2) == 0;
                var xPos = canvasRotation > 0 ?
                            width - Helper.mapToRange(i, minValue, maxValue, width) :
                            Helper.mapToRange(i, minValue, maxValue, width);

                ctx.lineWidth = major ? 3 : 2;
                ctx.beginPath();
                ctx.moveTo(xPos, 0);
                ctx.lineTo(xPos, major ? majorTickSize : minorTickSize);
                ctx.stroke();

                if (major) {
                    ctx.save();
                    ctx.translate(xPos, textOrigin);
                    ctx.rotate(-canvasRotation * Math.PI / 180);
                    ctx.fillText(i, 0, 2);
                    ctx.restore();
                }
            }

            var markWidth = canvasRotation > 0 ? label.height : -label.height;
            ctx.clearRect(width / 2 - markWidth / 2, 1, markWidth, height);

            ctx.lineWidth = 2;
            ctx.beginPath();
            ctx.moveTo(width / 2 - markWidth / 2, majorTickSize);
            ctx.lineTo(width / 2, 2);
            ctx.lineTo(width / 2 + markWidth / 2, majorTickSize);

            ctx.stroke();
            ctx.restore();
        }
    }

    Text {
        id: label
        anchors.centerIn: parent
        width: canvas.height
        color: root.color
        horizontalAlignment: Text.AlignHCenter
        font.bold: true
        font.pixelSize: fontPixelSize * 1.15
        text: prefix + "\n" + value
    }
}
