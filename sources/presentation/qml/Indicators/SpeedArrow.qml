import QtQuick 2.6
import "qrc:/JS/helper.js" as Helper

Item {
    id: root

    property int fix: -1
    property color color: {
        switch (fix) {
        case -1:
        case 0: return palette.sunkenColor;
        case 1: return palette.dangerColor;
        case 2: return palette.cautionColor;
        case 3:
        default: return palette.positiveColor;
        }
    }

    onFixChanged: canvas.requestPaint()
    onWidthChanged: canvas.requestPaint()
    onHeightChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.fill: parent
        onPaint: {
            var ctx = canvas.getContext('2d');

            ctx.clearRect(0, 0, width, height);

            ctx.save();
            ctx.translate(width / 2, height / 2);

            ctx.lineWidth = 1;
            ctx.strokeStyle = color;
            ctx.fillStyle = color;
            ctx.textBaseline = 'middle';
            ctx.textAlign = 'center';

            ctx.beginPath();
            ctx.moveTo(0, -height / 2);
            ctx.lineTo(width * 0.05, height * 0.15 - height / 2);
            ctx.lineTo(0, height * 0.1 - height / 2);
            ctx.lineTo(-width * 0.05, height * 0.15 - height / 2);
            ctx.closePath();
            ctx.fill();

            ctx.restore();
        }
    }
}

