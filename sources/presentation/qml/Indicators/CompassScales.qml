import QtQuick 2.6

Canvas {
    id: root

    property int heading: 0
    property color color: palette.textColor
    property int fontPixelSize: palette.fontPixelSize

    onHeadingChanged: root.requestPaint();
    onColorChanged: root.requestPaint();

    onPaint: {
        var ctx = root.getContext('2d');

        ctx.clearRect(0, 0, width, height);

        ctx.save();
        ctx.beginPath();

        ctx.lineWidth = 2;
        ctx.strokeStyle = color;
        ctx.fillStyle = color;
        ctx.font = fontPixelSize + 'px sans-serif';
        ctx.textBaseline = 'middle';
        ctx.textAlign = 'center';

        ctx.translate(width / 2, height / 2);
        ctx.rotate(-heading * Math.PI / 180);

        for (var i = 0; i <= 360; i += 15) {
            ctx.save();
            ctx.rotate(i * Math.PI / 180);
            ctx.translate(0, -height / 2);

            ctx.moveTo(0, fontPixelSize * 2);

            if (i % 30) {
                ctx.lineTo(0, fontPixelSize * 2.2);
            }
            else {
                ctx.lineTo(0, fontPixelSize * 2.4);

                ctx.save();
                ctx.translate(0, fontPixelSize);
                ctx.rotate((-i + heading) * Math.PI / 180);

                if (i == 0) ctx.fillText(qsTr("N"), 0, 2);
                if (i == 30) ctx.fillText("3", 0, 2);
                if (i == 60) ctx.fillText("6", 0, 2);
                if (i == 90) ctx.fillText(qsTr("E"), 0, 2);
                if (i == 120) ctx.fillText("12", 0, 2);
                if (i == 150) ctx.fillText("15", 0, 2);
                if (i == 180) ctx.fillText(qsTr("S"), 0, 2);
                if (i == 210) ctx.fillText("21", 0, 2);
                if (i == 240) ctx.fillText("24", 0, 2);
                if (i == 270) ctx.fillText(qsTr("W"), 0, 2);
                if (i == 300) ctx.fillText("30", 0, 2);
                if (i == 330) ctx.fillText("33", 0, 2);

                ctx.restore();
            }

            ctx.restore();
        }

        ctx.stroke();
        ctx.restore();
    }
}
