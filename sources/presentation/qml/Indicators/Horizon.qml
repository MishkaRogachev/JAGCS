import QtQuick 2.6
import "qrc:/JS/helper.js" as Helper

Canvas {
    id: root

    property bool available: true

    property int pitch: 0
    property int roll: 0
    property int minPitch: -25
    property int maxPitch: 25

    property int effectiveHeight: height

    onRollChanged: root.requestPaint()
    onPitchChanged: root.requestPaint()
    onWidthChanged: root.requestPaint()
    onHeightChanged: root.requestPaint()

    onPaint: {
        var ctx = root.getContext('2d');

        ctx.clearRect(0, 0, width, height);

        var size = 10000;
        var offset = Helper.mapToRange(pitch, minPitch, maxPitch,
                                       effectiveHeight);
        ctx.save();

        ctx.translate(width / 2, height / 2);
        ctx.rotate(-roll * Math.PI / 180);
        ctx.translate(0, offset - effectiveHeight / 2);

        ctx.fillStyle = available ? palette.skyColor : palette.disabledColor;
        ctx.fillRect(-size / 2, -size / 2, size, size / 2);

        ctx.fillStyle = available ? palette.groundColor : palette.disabledColor;
        ctx.fillRect(-size / 2, 0, size, size / 2);


        ctx.lineWidth = 1;
        ctx.strokeStyle = palette.textColor;
        ctx.beginPath();
        ctx.moveTo(-size / 2, 0);
        ctx.lineTo(size / 2, 0);
        ctx.stroke();

        ctx.restore();
    }
}
