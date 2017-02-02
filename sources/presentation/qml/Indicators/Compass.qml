import QtQuick 2.0

import QtQuick 2.6
import QtGraphicalEffects 1.0

Rectangle {
    id: root

    property real heading: 0
    property real course: 0
    property real trackAngle:0

    height: width
    radius: width / 2
    color: palette.sunkenColor
    clip: true

    Image {
        anchors.centerIn: parent
        rotation: heading
        source: "qrc:/indicators/plane_map_mark.svg"
    }
}
