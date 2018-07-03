import QtQuick 2.6
import "qrc:/JS/helper.js" as Helper

Item {
    id: root

    property bool guided: false
    property real heading: 0
    property real targetBearing: 0
    property real desiredHeading: 0
    property real trackError: 0
    property real maxTrackError: 100

    property real scalesRatio: 0.08
    property real scalesOffset: root.width * scalesRatio
    property real minorTickOffset: 0.5 * scalesOffset
    property real majorTickOffset: 1.0 * scalesOffset
    property real textOffset: 1.4 * scalesOffset

    onGuidedChanged: canvas.requestPaint()
    onTargetBearingChanged: canvas.requestPaint()
    onDesiredHeadingChanged: canvas.requestPaint()
    onTrackErrorChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.fill: parent
        anchors.margins: textOffset + majorTickOffset
        visible: guided

        onPaint: {
            var ctx = canvas.getContext('2d');

            ctx.clearRect(0, 0, width, height);

            ctx.save();
            ctx.translate(width / 2, height / 2);
            ctx.rotate(-heading * Math.PI / 180);

            ctx.lineWidth = 1;
            ctx.strokeStyle = customPalette.activeMissionColor;
            ctx.fillStyle = customPalette.activeMissionColor;
            ctx.textBaseline = 'middle';
            ctx.textAlign = 'center';

            ctx.save();
            ctx.rotate(targetBearing * Math.PI / 180);

            ctx.beginPath();
            ctx.moveTo(0, -height / 2);
            ctx.lineTo(minorTickOffset, majorTickOffset - height / 2);
            ctx.lineTo(0, minorTickOffset - height / 2);
            ctx.lineTo(-minorTickOffset, majorTickOffset - height / 2);
            ctx.closePath();
            ctx.fill();

            ctx.beginPath();
            ctx.lineWidth = 4;

            ctx.moveTo(0, minorTickOffset - height / 2);
            ctx.lineTo(0, -height / 4 - 1);

            ctx.moveTo(0, height / 4 + 1);
            ctx.lineTo(0, height / 2);
            ctx.stroke();
            ctx.restore();

            ctx.save();
            ctx.rotate(desiredHeading * Math.PI / 180);
            ctx.translate(Helper.mapToRange(trackError, 0, maxTrackError, width), 0);

            ctx.beginPath();
            ctx.lineWidth = 4;
            ctx.moveTo(0, -height / 4 + 1);
            ctx.lineTo(0, height / 4 - 1);
            ctx.stroke();
            ctx.restore();
            ctx.restore();
        }
    }
}
