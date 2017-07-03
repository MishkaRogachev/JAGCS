import QtQuick 2.6
import "qrc:/JS/helper.js" as Helper

Compass {
    id: root

    property bool guided: false
    property real targetBearing: 0
    property real trackError: 0
    property real maxTrackError: 100

    onGuidedChanged: canvas.requestPaint()
    onTargetBearingChanged: canvas.requestPaint()
    onTrackErrorChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.fill: parent
        anchors.margins: scalesOffset * 2
        rotation: targetBearing - heading
        visible: guided

        onPaint: {
            var ctx = canvas.getContext('2d');

            ctx.clearRect(0, 0, width, height);

            ctx.save();

            // Scales Mark
            ctx.beginPath();

            ctx.lineWidth = 1;
            ctx.strokeStyle = palette.activeMissionColor;
            ctx.fillStyle = palette.activeMissionColor;
            ctx.textBaseline = 'middle';
            ctx.textAlign = 'center';

            ctx.moveTo(width / 2, 0);
            ctx.lineTo(width / 2 + width * 0.05, height * 0.15);
            ctx.lineTo(width / 2, height * 0.1);
            ctx.lineTo(width / 2 - width * 0.05, height * 0.15);
            ctx.closePath();
            ctx.fill();

            ctx.beginPath();
            ctx.lineWidth = 6;

            ctx.moveTo(width / 2, height * 0.1);
            ctx.lineTo(width / 2, height / 4 - 1);

            var deviation = Helper.mapToRange(trackError, 0, maxTrackError, width);

            ctx.moveTo(width / 2 - deviation, height / 4 + 1);
            ctx.lineTo(width / 2 - deviation, 3 * height / 4 - 1);

            ctx.moveTo(width / 2, 3 * height / 4 + 1);
            ctx.lineTo(width / 2, height);

            ctx.stroke();
            ctx.restore();
        }
    }
}
