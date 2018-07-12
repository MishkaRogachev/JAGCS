import QtQuick 2.6
import "qrc:/JS/helper.js" as Helper

Canvas {
    id: root

    property real value: minValue
    property real minValue: 0
    property real maxValue: 100
    property color fillColor: customPalette.highlightColor

    Behavior on value { PropertyAnimation { duration: 100 } }

    onValueChanged: requestPaint()
    onMinValueChanged: requestPaint()
    onMaxValueChanged: requestPaint()
    onFillColorChanged: requestPaint()

    onPaint: {
        var ctx = root.getContext('2d');

        ctx.clearRect(0, 0, width, height);

        ctx.fillStyle = customPalette.backgroundColor;
        ctx.fillRect(0, 0, width, height);

        var offset = Helper.mapToRange(value, minValue, maxValue, height);
        var zero = Helper.mapToRange(0, minValue, maxValue, height);

        ctx.save();

        ctx.beginPath();
        ctx.fillStyle = fillColor;
        ctx.fillRect(1, height - zero, width - 2, zero - offset);

        ctx.restore();
    }
}
