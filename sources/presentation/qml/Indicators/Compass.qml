import QtQuick 2.6

Rectangle {
    id: root

    property real heading: 0
    property real course: 0
    property real windDirection: 0
    property real homeDirection: 0
    property real missionDirection: 0

    property color scalesColor: palette.textColor
    property color courseColor: palette.textColor
    property color windColor: palette.skyColor
    property int fontPixelSize: palette.fontPixelSize

    onHeadingChanged: canvas.requestPaint();
    onCourseChanged: canvas.requestPaint();
    onWindDirectionChanged: canvas.requestPaint();

    height: width
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

            // Scales Mark
            ctx.beginPath();

            ctx.lineWidth = 2;
            ctx.strokeStyle = scalesColor;
            ctx.fillStyle = scalesColor;
            ctx.textBaseline = 'middle';
            ctx.textAlign = 'center';

            ctx.translate(width / 2, height / 2);

            ctx.save();
            ctx.rotate(-heading * Math.PI / 180);

            for (var i = 0; i <= 360; i += 15) {
                ctx.save();
                ctx.rotate(i * Math.PI / 180);
                ctx.translate(0, -height / 2);

                ctx.moveTo(0, fontPixelSize * 2);

                if (i % 30) {
                    ctx.lineTo(0, fontPixelSize * 1.8);
                }
                else {
                    ctx.lineTo(0, fontPixelSize * 1.6);

                    ctx.save();
                    ctx.translate(0, fontPixelSize);
                    ctx.rotate((-i + heading) * Math.PI / 180);

                    ctx.font = 'bold ' + fontPixelSize + 'px sans-serif';
                    if (i == 0) ctx.fillText(qsTr("N"), 0, 2);
                    else if (i == 90) ctx.fillText(qsTr("E"), 0, 2);
                    else if (i == 180) ctx.fillText(qsTr("S"), 0, 2);
                    else if (i == 270) ctx.fillText(qsTr("W"), 0, 2);

                    ctx.font = fontPixelSize * 0.8 + 'px sans-serif';
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

            // Course Mark
            if (course > -1) {
                ctx.beginPath();
                ctx.strokeStyle = courseColor;

                ctx.save();
                ctx.rotate(course * Math.PI / 180);
                ctx.translate(0, -height / 2);

                ctx.moveTo(-fontPixelSize / 1.5, fontPixelSize * 2.5);
                ctx.lineTo(0, fontPixelSize * 2);
                ctx.lineTo(fontPixelSize / 1.5, fontPixelSize * 2.5);

                ctx.restore();
                ctx.stroke();
            }

            // Wind direction
            if (windDirection > -1) {
                ctx.beginPath();
                ctx.strokeStyle = windColor;

                ctx.save();
                ctx.rotate(windDirection * Math.PI / 180);

                for (var i = -height / 4; i < height / 4;
                     i+= fontPixelSize / 1.5) {
                    ctx.moveTo(-fontPixelSize / 3, i + fontPixelSize / 2);
                    ctx.lineTo(0, i);
                    ctx.lineTo(fontPixelSize / 3, i + fontPixelSize / 2);
                }

                ctx.restore();
                ctx.stroke();
            }

            ctx.restore();
            ctx.restore();
        }
    }

    CompassItem {
        anchors.centerIn: parent
        width: root.width
        height: root.height
        rotation: homeDirection - heading
        visible: homeDirection > -1
        iconSource: "qrc:/icons/home.svg"
    }

    CompassItem {
        anchors.centerIn: parent
        width: root.width
        height: root.height
        rotation: missionDirection - heading
        visible: missionDirection > -1
    }

    Image {
        anchors.centerIn: parent
        source: "qrc:/indicators/plane_map_mark.svg"
        width: root.width / 2
        height: width
    }
}
