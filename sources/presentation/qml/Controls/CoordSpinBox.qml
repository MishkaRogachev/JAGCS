import QtQuick 2.6
import QtQuick.Controls 2.0

import "qrc:/JS/helper.js" as Helper
import "./"

Control {
    id: control

    property real value: 0
    property real stepSize: 0.001
    property bool longitude: false

    implicitWidth: Math.max(background.implicitWidth,
                            contentItem.implicitWidth +
                            2 * padding +
                            up.implicitWidth +
                            down.implicitWidth)
    implicitHeight: palette.controlBaseSize
    font.pointSize: palette.fontSize
    leftPadding: -(up.width + down.width) / 2
    rightPadding: 6 + control.mirrored ? down.width : up.width

    background: Rectangle {
        color: control.enabled ? palette.sunkenColor : palette.disabledColor
    }

    contentItem: TextInput {
        text: Helper.degreesToDmsString(value, longitude)
        onEditingFinished: value =  Helper.dmsStringToDegree(text, longitude)
        font: control.font
        color: palette.textColor
        selectionColor: palette.highlightColor
        selectedTextColor: color
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        validator: RegExpValidator {
            regExp: /[0-9]{1,3}[°][0-9]{1,2}['][0-9]{1,2}[.][0-9]{1,2}"[N,S,W,E]/
        }
    }

    Button {
        id: down
        x: control.mirrored ? up.width : control.width - width - up.width
        height: control.height
        width: height
        backgroundColor: pressed ? palette.highlightColor : "transparent"
        iconSource: "qrc:/ui/minus.svg"
        onClicked: value -= stepSize
        autoRepeat: true
    }

    Button {
        id: up
        x: control.mirrored ? 0 : control.width - width
        height: control.height
        width: height
        backgroundColor: pressed ? palette.highlightColor : "transparent"
        iconSource: "qrc:/ui/plus.svg"
        onClicked: value += stepSize
        autoRepeat: true
    }
}
