import QtQuick 2.6
import "qrc:/JS/helper.js" as Helper

RollScale {
    id: rollScale

    property bool inputEnabled: false
    property real inputValue: 0
    property real inputMin: -1
    property real inputMax: 1
    property color inputColor: palette.cautionColor

    signal picked(real value)

    onInputValueChanged: canvas.requestPaint()
    onWidthChanged: canvas.requestPaint()
    onHeightChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.fill: parent
        onPaint: {
            var ctx = canvas.getContext('2d');

            ctx.clearRect(0, 0, width, height);

            ctx.lineWidth = 2;
            ctx.strokeStyle = inputColor;

            ctx.save();
            ctx.translate(width / 2, height / 2);
            var rotation = Math.max(Math.min(Helper.mapToRange(inputValue, inputMin, inputMax, height), maxRoll), minRoll);
            ctx.rotate(rotation * Math.PI / 180);

            ctx.beginPath();
            ctx.moveTo(-fontPixelSize / 2, -height / 2 - fontPixelSize / 2);
            ctx.lineTo(fontPixelSize / 2, -height / 2 + fontPixelSize / 2);
            ctx.moveTo(fontPixelSize / 2, -height / 2 - fontPixelSize / 2);
            ctx.lineTo(-fontPixelSize / 2, -height / 2 + fontPixelSize / 2);
            ctx.stroke();

            ctx.restore();
        }
    }
}
