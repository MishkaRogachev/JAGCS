import QtQuick 2.6

import "qrc:/JS/helper.js" as Helper

Canvas {
    id: root

    property real deviationX: 0.0
    property real deviationY: 0.0
    property real sizeX: 90.0
    property real sizeY: 90.0

    property color color: customPalette.textColor

    onWidthChanged: requestPaint()
    onHeightChanged: requestPaint()
    onDeviationXChanged: requestPaint()
    onDeviationYChanged: requestPaint()
    onSizeXChanged: requestPaint()
    onSizeYChanged: requestPaint()

    implicitHeight: width
    clip: true

    onPaint: {
        var ctx = root.getContext('2d');

        ctx.clearRect(0, 0, width, height);

        ctx.save();

        ctx.strokeStyle = color;

        ctx.translate(width / 2, height / 2);
        ctx.save();

        ctx.lineWidth = 2;
        ctx.beginPath();
        ctx.arc(0, 0, height * 0.1, 0, 2 * Math.PI, false);
        ctx.stroke();

        ctx.lineWidth = 1;
        ctx.beginPath();
        var size = height * 0.025;
        var spacing = height * 0.1;
        for (var i = -5; i < 6; ++i) {
            if (i == 0) continue;

            ctx.moveTo(-size, i * spacing);
            ctx.lineTo(size, i * spacing);
            ctx.moveTo(i * spacing, -size);
            ctx.lineTo(i * spacing, size);
        }
        ctx.stroke();

        var dx = Helper.mapToRange(deviationX, 0, sizeX, width / 2);
        var dy = Helper.mapToRange(deviationY, 0, sizeY, height / 2);

        ctx.beginPath();
        ctx.moveTo(dx, -height * 0.5);
        ctx.lineTo(dx, height * 0.5);
        ctx.moveTo(-height * 0.5, dy);
        ctx.lineTo(height * 0.5, dy);
        ctx.stroke();

        ctx.restore();
    }
}
