import QtQuick 2.6

import "../Controls" as Controls

Ladder {
    id: root

    property bool controlEnabled: true

    signal setValue(real newValue)

    Controls.Button {
        iconSource: "qrc:/icons/up.svg"
        flat: true
        x: root.mirrored ? root.width - width : 0
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -parent.height / 3
        visible: controlEnabled
        onClicked: setValue(targetValue + 1)
    }

    Controls.Button {
        iconSource: "qrc:/icons/down.svg"
        flat: true
        x: root.mirrored ? root.width - width : 0
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: parent.height / 3
        visible: controlEnabled
        onClicked: setValue(targetValue - 1)
    }
}
