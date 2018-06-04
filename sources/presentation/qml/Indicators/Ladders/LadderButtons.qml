import QtQuick 2.6

import "qrc:/Controls" as Controls

Item {
    id: root

    property bool mirrored: parent.mirrored
    property bool inputEnabled: false

    signal addValue(real value)

    Controls.Button {
        anchors.left: mirrored ? undefined : parent.left
        anchors.right: mirrored ? parent.right : undefined
        anchors.verticalCenter: root.verticalCenter
        anchors.verticalCenterOffset: -root.height / 3
        iconSource: "qrc:/icons/arrow_up.svg"
        flat: true
        round: true
        visible: inputEnabled
        autoRepeat: true
        onClicked: addValue(0.05)
    }

    Controls.Button {
        anchors.left: mirrored ? undefined : parent.left
        anchors.right: mirrored ? parent.right : undefined
        anchors.verticalCenter: root.verticalCenter
        anchors.verticalCenterOffset: root.height / 3
        iconSource: "qrc:/icons/arrow_down.svg"
        flat: true
        round: true
        visible: inputEnabled
        autoRepeat: true
        onClicked: addValue(-0.05)
    }
}
