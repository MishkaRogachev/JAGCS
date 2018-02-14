import QtQuick 2.6
import "qrc:/JS/helper.js" as Helper

import "../Shaders" as Shaders

Item {
    id: root

    property real value: 0
    property real error: 0
    property real warningValue: minValue
    property real minValue: 0
    property real maxValue: 100
    property real valueStep: 20

    property real fontPixelSize: height * 0.1
    property real fontScaleSize: fontPixelSize
    property real minorTickSize: fontScaleSize * 0.4
    property real majorTickSize: fontScaleSize * 0.6
    property real textOrigin: fontScaleSize * 0.8
    property bool mirrored: false

    property bool operational: false
    property string prefix
    property string suffix
    property color color: operational ? palette.textColor : palette.dangerColor
    property alias warningColor: hatch.color

    clip: true
    opacity: enabled ? 1 : 0.33
    implicitWidth: label.implicitWidth + majorTickSize * 2
    onWidthChanged: canvas.requestPaint()
    onHeightChanged: canvas.requestPaint()
    onColorChanged: canvas.requestPaint()
    onValueChanged: canvas.requestPaint()

    Shaders.OpacityBorder {
        anchors.fill: parent
        sourceItem: canvas
    }

    Canvas {
        id: canvas
        anchors.fill: parent
        onPaint: {
            var ctx = canvas.getContext('2d');

            ctx.clearRect(0, 0, width, height);

            ctx.strokeStyle = color;
            ctx.fillStyle = color;
            ctx.font = 'bold ' + fontScaleSize + 'px "Open Sans"';
            ctx.textAlign = mirrored ? 'left' : 'right';
            ctx.textBaseline = 'middle';

            // Vertical line
            ctx.save();
            ctx.lineWidth = 1;
            ctx.translate(mirrored ? ctx.lineWidth : width - ctx.lineWidth, 0);
            ctx.beginPath();
            ctx.moveTo(0, 0);
            ctx.lineTo(0, height);
            ctx.stroke();

            // Ticks
            var counter = 0;
            for (var i = minValue - (minValue % valueStep); i <= maxValue;
                 i += (valueStep / 2)) {

                var major = (counter++ % 2) == 0;
                var pos = height - Helper.mapToRange(i, minValue, maxValue, height)
                var tick = major ? majorTickSize : minorTickSize;

                ctx.lineWidth = major ? 2 : 1;
                ctx.beginPath();
                ctx.moveTo(0, pos);
                ctx.lineTo(mirrored ? tick : -tick, pos);
                ctx.stroke();

                if (major) ctx.fillText(i, mirrored ? 2 + textOrigin : -2 - textOrigin, pos);
            }

            // Clear rect for current value
            var markHeight = label.height;
            ctx.clearRect(mirrored ? 1 : -1, height / 2 - markHeight / 2,
                          mirrored ? width : -width, markHeight);

            // Arrow for current value
            ctx.lineWidth = 2;
            ctx.beginPath();
            ctx.moveTo(mirrored ? majorTickSize : -majorTickSize, height / 2 - markHeight / 2);
            ctx.lineTo(mirrored ? 2 : -2, height / 2);
            ctx.lineTo(mirrored ? majorTickSize : -majorTickSize, height / 2 + markHeight / 2);
            ctx.stroke();

            // Error mark
            if (error) {
                ctx.lineWidth = 4;
                ctx.strokeStyle = palette.activeMissionColor;
                var errorPos = height - Helper.mapToRange(value + error, minValue, maxValue, height);

                ctx.beginPath();
                ctx.moveTo(0, errorPos);
                ctx.lineTo(mirrored ? majorTickSize : -majorTickSize, errorPos);
                ctx.stroke();
            }

            ctx.restore();
        }

        Shaders.Hatch {
            id: hatch
            anchors.left: parent.left
            anchors.leftMargin: mirrored ? 10 : 0
            anchors.right: parent.right
            anchors.rightMargin: mirrored ? 0 : 10
            anchors.bottom: parent.bottom
            height: Helper.mapToRange(warningValue, minValue, maxValue, parent.height)
            xFactor: yFactor * height / width
            yFactor: 35
            z: -1
        }
    }

    FdLabel {
        id: label
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: mirrored ? majorTickSize * 0.5 : -majorTickSize * 0.5
        width: parent.width - majorTickSize
        value: root.value
        prefix: root.prefix
        operational: root.operational
    }
}
