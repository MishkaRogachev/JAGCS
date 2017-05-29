import QtQuick 2.6

Rectangle {
    id: root

    property real course: 0
    property real heading: 0
    property int tickFactor: 5
    property real scalesRatio: 0.08
    property color scalesColor: palette.textColor
    property int scalesOffset: root.width * scalesRatio

    onCourseChanged: canvas.requestPaint()
    onHeadingChanged: canvas.requestPaint()

    implicitHeight: width
    radius: width / 2
    color: palette.sunkenColor
    clip: true

    Canvas {
        id: canvas
        anchors.fill: parent

        onPaint: {
            var ctx = canvas.getContext('2d');

            ctx.clearRect(0, 0, width, height);

            ctx.save();
            ctx.rotate(-course)

            // Scales Mark
            ctx.beginPath();

            ctx.lineWidth = 2;
            ctx.strokeStyle = scalesColor;
            ctx.fillStyle = scalesColor;
            ctx.textBaseline = 'middle';
            ctx.textAlign = 'center';

            ctx.translate(width / 2, height / 2);

            ctx.save();

            for (var i = 0; i <= 360; i += tickFactor) {
                ctx.save();
                ctx.rotate(i * Math.PI / 180);
                ctx.translate(0, -height / 2);

                if (i % 10) {
                    ctx.moveTo(0, 0)
                    ctx.lineTo(0, scalesOffset * 0.25);
                }
                else {
                    ctx.moveTo(0, 0)
                    ctx.lineTo(0, scalesOffset * 0.5);
                }

                if (!(i % 30)) {
                    ctx.save();
                    ctx.translate(0, scalesOffset * 1.3);
                    ctx.rotate((-i + course) * Math.PI / 180);

                    ctx.font = 'bold ' + scalesOffset * 1.2 + 'px "Open Sans"';
                    if (i == 0) ctx.fillText(qsTr("N"), 0, 2);
                    else if (i == 90) ctx.fillText(qsTr("E"), 0, 2);
                    else if (i == 180) ctx.fillText(qsTr("S"), 0, 2);
                    else if (i == 270) ctx.fillText(qsTr("W"), 0, 2);

                    ctx.font = scalesOffset + 'px "Open Sans"';
                    if (i == 30) ctx.fillText("3", 0, 2);
                    else if (i == 60) ctx.fillText("6", 0, 2);
                    else if (i == 120) ctx.fillText("12", 0, 2);
                    else if (i == 150) ctx.fillText("15", 0, 2);
                    else if (i == 210) ctx.fillText("21", 0, 2);
                    else if (i == 240) ctx.fillText("24", 0, 2);
                    else if (i == 300) ctx.fillText("30", 0, 2);
                    else if (i == 330) ctx.fillText("33", 0, 2);

                    ctx.restore();
                }

                ctx.restore();
            }

            ctx.stroke();

            ctx.restore();

            ctx.save();

            ctx.rotate((course - heading) * Math.PI / 180);
            ctx.beginPath();
            ctx.lineWidth = 4;
            ctx.moveTo(-scalesOffset, scalesOffset - (ctx.lineWidth + height) / 2);
            ctx.lineTo(0, (ctx.lineWidth - height) / 2);
            ctx.lineTo(scalesOffset, scalesOffset - (ctx.lineWidth + height) / 2);
            ctx.stroke();
            ctx.restore();

            ctx.restore();
        }
    }
}
