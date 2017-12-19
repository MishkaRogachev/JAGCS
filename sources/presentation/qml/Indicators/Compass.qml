import QtQuick 2.6

Canvas {
    id: root

    property real heading: 0
    property real course: 0

    property color color: palette.textColor
    property color courseColor: palette.positiveColor
    property bool courseEnabled: true
    property url mark
    property int tickFactor: 5
    property real scalesRatio: 0.08
    property real scalesOffset: root.width * scalesRatio
    property real minorTickOffset: 0.4 * scalesOffset
    property real majorTickOffset: 0.8 * scalesOffset
    property real textOffset: 1.4 * scalesOffset

    onWidthChanged: requestPaint()
    onHeightChanged: requestPaint()
    onCourseChanged: requestPaint()
    onHeadingChanged: requestPaint()
    onColorChanged: requestPaint()

    implicitHeight: width
    clip: true

    onPaint: {
        var ctx = root.getContext('2d');

        ctx.clearRect(0, 0, width, height);

        ctx.save();

        ctx.strokeStyle = color;
        ctx.fillStyle = color;
        ctx.textBaseline = 'middle';
        ctx.textAlign = 'center';

        ctx.translate(width / 2, height / 2);
        ctx.save();

        // Scales
        for (var i = 0; i <= 360; i += tickFactor) {
            ctx.lineWidth = i % 30 ? 1 : 2;
            ctx.beginPath();
            ctx.save();
            ctx.rotate((i - heading) * Math.PI / 180);
            ctx.translate(0, -height / 2);

            if (i % 10) {
                ctx.moveTo(0, textOffset + majorTickOffset - minorTickOffset);
                ctx.lineTo(0, textOffset + majorTickOffset);
            }
            else {
                ctx.moveTo(0, textOffset);
                ctx.lineTo(0, textOffset + majorTickOffset);
            }

            if (!(i % 30)) {
                ctx.save();
                ctx.translate(0, textOffset / 2);
                ctx.rotate((-i + heading) * Math.PI / 180);

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
            ctx.stroke();
        }
        ctx.restore();

        // Course Mark
        if (courseEnabled) {
            ctx.strokeStyle = courseColor;
            ctx.save();
            ctx.rotate((course - heading) * Math.PI / 180);
            ctx.beginPath();
            ctx.lineWidth = 4;
            ctx.moveTo(-scalesOffset, scalesOffset - (ctx.lineWidth + height) / 2);
            ctx.lineTo(0, (ctx.lineWidth - height) / 2);
            ctx.lineTo(scalesOffset, scalesOffset - (ctx.lineWidth + height) / 2);
            ctx.stroke();
            ctx.restore();
        }

        ctx.restore();
    }

    Image {
        anchors.centerIn: parent
        source: mark
        width: parent.width / 1.5
        height: width
        z: 1
    }
}
