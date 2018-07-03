import QtQuick 2.6
import "qrc:/JS/helper.js" as Helper

Item {
    id: root

    property real value: 0.0
    property real border: 180.0

    onValueChanged: canvas.requestPaint()
    onBorderChanged: canvas.requestPaint()
    onWidthChanged: canvas.requestPaint()
    onHeightChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.fill: parent
        onPaint: {
            var ctx = canvas.getContext('2d');

            ctx.clearRect(0, 0, width, height);

            var x = canvas.width / 2;
            var y = canvas.height / 2;
            var radius = canvas.height * 0.42;

            ctx.beginPath();
            ctx.lineCap = 'round';
            ctx.strokeStyle = customPalette.backgroundColor;
            ctx.lineWidth = canvas.height * 0.06;
            ctx.arc(x, y, radius, 0.4 * Math.PI, 0.6 * Math.PI, false);
            ctx.stroke();

            ctx.beginPath();
            ctx.strokeStyle = customPalette.textColor;
            ctx.lineWidth = canvas.height * 0.05;
            var angle = Helper.mapToRange(value, -border, border, 0.2);
            ctx.arc(x, y, radius, (0.399 + angle) * Math.PI, (0.401 + angle) * Math.PI, false);
            ctx.stroke();
        }
    }
}
