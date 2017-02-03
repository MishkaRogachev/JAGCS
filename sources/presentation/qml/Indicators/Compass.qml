import QtQuick 2.6
import QtGraphicalEffects 1.0

Rectangle {
    id: root

    property alias heading: scales.heading
    property real course: 0
    property real trackAngle: 0

    property real windAngle: 0
    property real homeAngle: 0

    property alias scalesColor: scales.color

    height: width
    radius: width / 2
    color: palette.sunkenColor
    clip: true

    CompassScales {
        id: scales
        anchors.fill: parent
    }

    Image {
        anchors.centerIn: parent
        source: "qrc:/indicators/plane_map_mark.svg"
        width: root.width / 2
        height: width
    }
}
