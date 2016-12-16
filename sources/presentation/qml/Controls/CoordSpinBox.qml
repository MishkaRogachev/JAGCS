import QtQuick 2.6
import QtQuick.Controls 2.0

import "qrc:/JS/helper.js" as Helper
import "./"

Control { // TODO: RealSpinBox
    id: control

    property real value: 0
    property real stepSize: 0.001
    property bool isLongitude: false

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
        border.color: input.activeFocus ? palette.highlightColor : "transparent"
    }

    contentItem: TextInput {
        id: input
        focus: true
        text: Helper.degreesToDmsString(value, isLongitude)
        onEditingFinished: value =  Helper.dmsStringToDegree(text, isLongitude)
        font: control.font
        color: palette.textColor
        selectionColor: palette.selectionColor
        selectedTextColor: palette.selectedTextColor
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        validator: RegExpValidator {
            regExp: /[0-9]{1,3}[°][0-9]{1,2}['][0-9]{1,2}[.][0-9]{1,2}"[N,S,W,E]/
        }
    }

    Button {
        id: down
        x: control.mirrored ? up.width : control.width - width - up.width
        flat: true
        iconSource: "qrc:/ui/minus.svg"
        onClicked: isNaN(value) ? value = -stepSize : value -= stepSize
        autoRepeat: true
    }

    Button {
        id: up
        x: control.mirrored ? 0 : control.width - width
        flat: true
        iconSource: "qrc:/ui/plus.svg"
        onClicked: Helper.isNaN(value) ? value = stepSize : value += stepSize
        autoRepeat: true
    }
}
