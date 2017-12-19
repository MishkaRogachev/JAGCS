import QtQuick 2.6
import "qrc:/JS/helper.js" as Helper

Compass {
    id: root

    property bool guided: false
    property real targetBearing: 0
    property real desiredHeading: 0
    property real trackError: 0
    property real maxTrackError: 100

    onGuidedChanged: canvas.requestPaint()
    onHeadingChanged: canvas.requestPaint()
    onTargetBearingChanged: canvas.requestPaint()
    onDesiredHeadingChanged: canvas.requestPaint()
    onTrackErrorChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.fill: parent
        anchors.margins: scalesOffset * 2
        visible: guided

        onPaint: {
            var ctx = canvas.getContext('2d');

            ctx.clearRect(0, 0, width, height);

            ctx.save();
            ctx.translate(width / 2, height / 2);
            ctx.rotate(-heading * Math.PI / 180);

            ctx.lineWidth = 1;
            ctx.strokeStyle = palette.activeMissionColor;
            ctx.fillStyle = palette.activeMissionColor;
            ctx.textBaseline = 'middle';
            ctx.textAlign = 'center';

            ctx.save();
            ctx.rotate(targetBearing * Math.PI / 180);

            ctx.beginPath();
            ctx.moveTo(0, -height / 2);
            ctx.lineTo(width * 0.05, height * 0.15 - height / 2);
            ctx.lineTo(0, height * 0.1 - height / 2);
            ctx.lineTo(-width * 0.05, height * 0.15 - height / 2);
            ctx.closePath();
            ctx.fill();

            ctx.beginPath();
            ctx.lineWidth = 4;

            ctx.moveTo(0, height * 0.1 - height / 2);
            ctx.lineTo(0, -height / 4 - 1);

            ctx.moveTo(0, height / 4 + 1);
            ctx.lineTo(0, height / 2);
            ctx.stroke();
            ctx.restore();

            ctx.save();
            ctx.rotate(desiredHeading * Math.PI / 180);
            ctx.translate(-Helper.mapToRange(trackError, 0, maxTrackError, width), 0);

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
