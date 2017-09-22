import QtQuick 2.6
import "qrc:/JS/helper.js" as Helper

Item {
    id: planeMark

    property int pitch: 0
    property int roll: 0
    property int effectiveHeight: height

    property color markColor: palette.activeMissionColor
    property int markWidth: 6

    onWidthChanged: canvas.requestPaint()
    onHeightChanged: canvas.requestPaint()
    onRollChanged: canvas.requestPaint()
    onPitchChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.fill: parent
        onPaint: {
            var ctx = canvas.getContext('2d');

            ctx.clearRect(0, 0, width, height);

            var offset = Helper.mapToRange(pitch, minPitch, maxPitch, effectiveHeight);

            ctx.lineWidth = markWidth;
            ctx.strokeStyle = markColor;
            ctx.fillStyle = markColor;

            ctx.save();
            ctx.beginPath();

            ctx.translate(width / 2, height / 2);
            ctx.rotate(-roll * Math.PI / 180);
            ctx.translate(0, offset - effectiveHeight / 2);

            ctx.moveTo(-width / 2, 0);
            ctx.lineTo(-width / 4, 0);

            ctx.moveTo(width / 4, 0);
            ctx.lineTo(width / 2, 0);

            ctx.stroke();
            ctx.restore();
        }
    }
}
