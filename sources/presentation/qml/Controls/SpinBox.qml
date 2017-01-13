import QtQuick 2.6
import QtQuick.Controls 2.0

import "./"

Control {
    id: control

    property real value: from
    property real from: 0
    property real to: 0
    property real stepSize: 1

    onValueChanged: {
        if (from >= to) return;
        if (value > to) value = to;
        if (value < from) value = from;
    }

    clip: true

    implicitWidth: Math.max(background.implicitWidth,
                            contentItem.implicitWidth +
                            2 * padding +
                            up.implicitWidth +
                            down.implicitWidth)
    implicitHeight: palette.controlBaseSize
    leftPadding: -(up.width + down.width) / 2
    rightPadding: 6 + control.mirrored ? down.width : up.width
    font.pointSize: palette.fontSize

    background: Rectangle {
        implicitWidth: palette.controlBaseWidth
        implicitHeight: palette.controlBaseSize
        color: {
            if (!control.enabled) return palette.disabledColor;
            if (isNaN(value)) return palette.negativeColor
            return palette.sunkenColor
        }
        border.color: contentItem.activeFocus ? palette.highlightColor : "transparent"
    }

    contentItem: TextInput {
        text: isNaN(value) ? 0 : value
        onEditingFinished: value = text
        font: control.font
        color: palette.textColor
        selectionColor: palette.selectionColor
        selectedTextColor: palette.selectedTextColor
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
    }

    Button {
        id: down
        x: control.mirrored ? up.width : control.width - width - up.width
        height: control.height
        flat: true
        iconSource: "qrc:/ui/minus.svg"
        onClicked: isNaN(value) ? value = -stepSize : value -= stepSize
        autoRepeat: true
        z: 1
    }

    Button {
        id: up
        x: control.mirrored ? 0 : control.width - width
        height: control.height
        flat: true
        iconSource: "qrc:/ui/plus.svg"
        onClicked: isNaN(value) ? value = stepSize : value += stepSize
        autoRepeat: true
        z: 1
    }
}
