import QtQuick 2.6
import "qrc:/JS/helper.js" as Helper

import "qrc:/Shaders" as Shaders

Item {
    id: root

    property bool mirrored: parent.mirrored
    property real majorTickSize: parent.majorTickSize

    property real value: 0
    property color color: customPalette.activeMissionColor

    onWidthChanged: canvas.requestPaint()
    onHeightChanged: canvas.requestPaint()
    onColorChanged: canvas.requestPaint()
    onValueChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.fill: parent
        onPaint: {
            var ctx = getContext('2d');

            ctx.clearRect(0, 0, width, height);

            ctx.fillStyle = color;
            ctx.strokeStyle = color;

            ctx.save();
            ctx.translate(mirrored ? ctx.lineWidth : width - ctx.lineWidth, 0);

            var errorPos = height - root.parent.mapToRange(value);

            ctx.beginPath();
            if (errorPos > height) {
                ctx.moveTo((mirrored ? majorTickSize : -majorTickSize) / 2, height);
                ctx.lineTo(0, height - majorTickSize);
                ctx.lineTo(mirrored ? majorTickSize : -majorTickSize, height - majorTickSize);
                ctx.fill();
            }
            else if (errorPos < 0) {
                ctx.moveTo((mirrored ? majorTickSize : -majorTickSize) / 2, 0);
                ctx.lineTo(0, majorTickSize);
                ctx.lineTo(mirrored ? majorTickSize : -majorTickSize, majorTickSize);
                ctx.fill();
            }
            else {
                ctx.lineWidth = 4;
                ctx.moveTo(0, errorPos);
                ctx.lineTo(mirrored ? majorTickSize : -majorTickSize, errorPos);
                ctx.stroke();
            }

            ctx.restore();
        }
    }
}
