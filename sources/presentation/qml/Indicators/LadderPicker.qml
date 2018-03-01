import QtQuick 2.6

import "../Controls" as Controls

Ladder {
    id: root

    property bool inputEnabled: false
    property real inputValue: 0

    signal addValue(real value)

    Controls.Button {
        anchors.centerIn: root
        anchors.verticalCenterOffset: -root.height / 3
        anchors.horizontalCenterOffset: mirrored ? root.width / 4 : -root.width / 4
        iconSource: "qrc:/icons/up.svg"
        flat: true
        round: true
        visible: inputEnabled
        autoRepeat: true
        onClicked: addValue(0.05)
    }

    Controls.Button {
        anchors.centerIn: root
        anchors.verticalCenterOffset: root.height / 3
        anchors.horizontalCenterOffset: mirrored ? root.width / 4 : -root.width / 4
        iconSource: "qrc:/icons/down.svg"
        flat: true
        round: true
        visible: inputEnabled
        autoRepeat: true
        onClicked: addValue(-0.05)
    }
}
