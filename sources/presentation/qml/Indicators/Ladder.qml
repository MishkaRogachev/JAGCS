import QtQuick 2.0
import "qrc:/JS/helper.js" as Helper

import "../Controls" as Controls
import "../Shaders" as Shaders

Item {
    id: root

    property int value: 0
    property int warningValue: minValue
    property int minValue: 0
    property int maxValue: 100
    property int valueStep: 20

    property int fontPixelSize: palette.fontPixelSize * 0.7
    property int minorTickSize: fontPixelSize * 0.4
    property int majorTickSize: fontPixelSize * 0.6
    property int textOrigin: fontPixelSize * 0.8
    property bool mirrored: false

    property bool operational: false
    property string prefix
    property string suffix
    opacity: enabled ? 1 : 0.33
    property color color: operational ? palette.textColor : palette.dangerColor
    property alias warningColor: hatch.color

    clip: true
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
            ctx.font = 'bold ' + fontPixelSize + 'px "Open Sans"';
            ctx.textAlign = mirrored ? 'left' : 'right';
            ctx.textBaseline = 'middle';
            
            ctx.save();
            ctx.translate(mirrored ? 2 : width - 2, 0);
            ctx.lineWidth = 2;
            ctx.beginPath();
            ctx.moveTo(0, 0);
            ctx.lineTo(0, height);

            ctx.moveTo(0, 2);
            ctx.lineTo(mirrored ? majorTickSize : -majorTickSize, 2);
            ctx.moveTo(0, height - 2);
            ctx.lineTo(mirrored ? majorTickSize : -majorTickSize, height - 2);
            ctx.stroke();

            var counter = 0;
            for (var i = minValue - (minValue % valueStep); i <= maxValue;
                 i += (valueStep / 2)) {

                var major = (counter++ % 2) == 0;
                var pos = height - Helper.mapToRange(i, minValue, maxValue, height)
                var tick = major ? majorTickSize : minorTickSize;

                ctx.lineWidth = major ? 3 : 2;
                ctx.beginPath();
                ctx.moveTo(0, pos);
                ctx.lineTo(mirrored ? tick : -tick, pos);
                ctx.stroke();

                if (major) ctx.fillText(i, mirrored ? 2 + textOrigin : -2 - textOrigin, pos);
                    //ctx.translate(textOrigin, pos);
            }

            var markHeight = label.height;
            ctx.clearRect(mirrored ? 1 : -1, height / 2 - markHeight / 2,
                          mirrored ? width : -width, markHeight);

            ctx.lineWidth = 2;
            ctx.beginPath();
            ctx.moveTo(mirrored ? majorTickSize : -majorTickSize, height / 2 - markHeight / 2);
            ctx.lineTo(mirrored ? 2 : -2, height / 2);
            ctx.lineTo(mirrored ? majorTickSize : -majorTickSize, height / 2 + markHeight / 2);

            ctx.stroke();
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

    Text {
        id: label
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: mirrored ? majorTickSize : -majorTickSize
        width: parent.width
        color: root.color
        horizontalAlignment: Text.AlignHCenter
        font.bold: true
        font.pixelSize: fontPixelSize * 1.15
        text: prefix + "\n" + value + " " + suffix
    }
}
