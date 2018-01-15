import QtQuick 2.6

Column {
    id: root

    property string prefix
    property int digits: 0
    property real value: 0
    property bool operational: true

    width: Math.max(defText.implicitWidth, valueText.implicitWidth)

    Text {
        id: defText
        width: root.width
        horizontalAlignment: Text.AlignHCenter
        opacity: enabled ? 1 : 0.33
        color: operational ? palette.textColor : palette.dangerColor
        font.bold: true
        font.pixelSize: sizings.fontPixelSize * 0.6
        visible: prefix.length > 0
        text: prefix
    }

    Text {
        id: valueText
        width: root.width
        horizontalAlignment: Text.AlignHCenter
        opacity: enabled ? 1 : 0.33
        color: operational ? palette.textColor : palette.dangerColor
        font.bold: true
        font.pixelSize: sizings.fontPixelSize * 0.75
        text: enabled ? value.toFixed(digits) : "-"
    }
}

