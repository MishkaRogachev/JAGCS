import QtQuick 2.6
import QtGraphicalEffects 1.0

import "../Controls" as Controls

Item {
    id: root

    property alias heading: hsi.heading
    property alias course: hsi.course
    property alias targetBearing: hsi.targetBearing
    property alias trackError: hsi.trackError

    implicitHeight: hsi.height

    SituationIndicator {
        id: hsi
        anchors.centerIn: parent
        width: parent.width * 0.6
    }
}
