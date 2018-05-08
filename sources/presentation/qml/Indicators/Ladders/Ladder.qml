import QtQuick 2.6
import "qrc:/JS/helper.js" as Helper

import "qrc:/Shaders" as Shaders
import ".."

Item {
    id: root

    property real value: 0
    property real error: 0
    property bool errorVisible: false
    property real warningValue: minValue
    property real minValue: 0
    property real maxValue: 100
    property real valueStep: 20

    property alias fontScaleSize: label.prefixFont.pixelSize
    property real minorTickSize: fontScaleSize * 0.4
    property real majorTickSize: fontScaleSize * 0.6
    property real textOrigin: fontScaleSize * 0.8
    property bool mirrored: false

    property bool operational: false
    property string prefix
    property string suffix
    property color color: operational ? customPalette.textColor : customPalette.dangerColor
    property alias warningColor: hatch.color

    function mapToRange(val) {
        return Helper.mapToRange(val, minValue, maxValue, height);
    }

    function mapFromRange(pos) {
        return Helper.mapFromRange(pos, minValue, maxValue, height);
    }

    implicitWidth: label.implicitWidth + majorTickSize * 2
    onWidthChanged: ladderCanvas.requestPaint()
    onHeightChanged: ladderCanvas.requestPaint()
    onColorChanged: {
        ladderCanvas.requestPaint()
        arrowCanvas.requestPaint()
    }
    onValueStepChanged: ladderCanvas.requestPaint()
    onValueChanged: {
        ladderCanvas.requestPaint()
        if (errorVisible) errorCanvas.requestPaint()
    }
    onErrorChanged: if (errorVisible) errorCanvas.requestPaint()

    Shaders.OpacityBorder {
        anchors.fill: ladderCanvas
        opacity: enabled ? 1 : 0.33
        source: ladderCanvas

        Shaders.Hatch {
            id: hatch
            anchors.left: parent.left
            anchors.leftMargin: mirrored ? 10 : 0
            anchors.right: parent.right
            anchors.rightMargin: mirrored ? 0 : 10
            anchors.bottom: parent.bottom
            height: mapToRange(warningValue)
            xFactor: yFactor * height / width
            yFactor: 35
            z: -1
        }
    }

    Canvas {
        id: ladderCanvas
        visible: false
        anchors.fill: parent
        onPaint: {
            var ctx = getContext('2d');

            ctx.clearRect(0, 0, width, height);

            ctx.strokeStyle = color;
            ctx.fillStyle = color;
            ctx.font = 'bold ' + fontScaleSize + 'px "Open Sans"';
            ctx.textAlign = mirrored ? 'left' : 'right';
            ctx.textBaseline = 'middle';

            ctx.save();
            ctx.translate(mirrored ? ctx.lineWidth : width - ctx.lineWidth, 0);

            // Vertical line
            ctx.lineWidth = 1;
            ctx.beginPath();
            ctx.moveTo(0, 0);
            ctx.lineTo(0, height);
            ctx.stroke();

            // Ticks
            var counter = 0;
            for (var i = minValue - (minValue % valueStep); i <= maxValue;
                 i += (valueStep / 2)) {

                var major = (counter++ % 2) == 0;
                var pos = height - mapToRange(i)
                var tick = major ? majorTickSize : minorTickSize;

                ctx.lineWidth = major ? 2 : 1;
                ctx.beginPath();
                ctx.moveTo(0, pos);
                ctx.lineTo(mirrored ? tick : -tick, pos);
                ctx.stroke();

                if (major) ctx.fillText(i, mirrored ? 2 + textOrigin : -2 - textOrigin, pos);
            }

            // Clear rect for current value
            ctx.clearRect(mirrored ? 1 : -1, height / 2 - label.height / 2,
                                     mirrored ? width : -width, label.height);
            ctx.restore();
        }
    }

    Canvas { // Error mark
        id: errorCanvas
        anchors.fill: parent
        visible: errorVisible
        onPaint: {
            var ctx = getContext('2d');

            ctx.clearRect(0, 0, width, height);

            ctx.save();
            ctx.translate(mirrored ? ctx.lineWidth : width - ctx.lineWidth, 0);

            var errorPos = height - mapToRange(value + error);

            ctx.beginPath();
            if (errorPos > height) {
                ctx.fillStyle = customPalette.activeMissionColor;
                ctx.moveTo((mirrored ? majorTickSize : -majorTickSize) / 2, height);
                ctx.lineTo(0, height - majorTickSize);
                ctx.lineTo(mirrored ? majorTickSize : -majorTickSize, height - majorTickSize);
                ctx.fill();
            }
            else if (errorPos < 0) {
                ctx.fillStyle = customPalette.activeMissionColor;
                ctx.moveTo((mirrored ? majorTickSize : -majorTickSize) / 2, 0);
                ctx.lineTo(0, majorTickSize);
                ctx.lineTo(mirrored ? majorTickSize : -majorTickSize, majorTickSize);
                ctx.fill();
            }
            else {
                ctx.lineWidth = 4;
                ctx.strokeStyle = customPalette.activeMissionColor;
                ctx.moveTo(0, errorPos);
                ctx.lineTo(mirrored ? majorTickSize : -majorTickSize, errorPos);
                ctx.stroke();
            }

            ctx.restore();
        }
    }

    Canvas { // Arrow for current value
        id: arrowCanvas
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: mirrored ? label.left : undefined
        anchors.left: mirrored ? undefined : label.right
        anchors.margins: -2
        width: majorTickSize
        height: label.height
        onPaint: {
            var ctx = getContext('2d');

            ctx.clearRect(0, 0, width, height);
            ctx.lineWidth = 2;

            ctx.strokeStyle = color;
            ctx.beginPath();
            ctx.moveTo(mirrored ? width : 0, 0);
            ctx.lineTo(mirrored ? 1 : width - 1, height / 2);
            ctx.lineTo(mirrored ? width : 0, height);
            ctx.stroke();
        }
    }

    ValueLabel {
        id: label
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: mirrored ? majorTickSize * 0.5 : -majorTickSize * 0.5
        width: parent.width - majorTickSize
        value: root.value
        prefix: root.prefix
        operational: root.operational
    }
}
