import QtQuick 2.6

Item {
    id: root

    property string prefix
    property int digits: 0
    property real value: NaN
    property bool operational: true
    property color color: operational ? customPalette.textColor : customPalette.dangerColor

    property alias prefixFont: prefixText.font
    property alias valueFont: valueText.font

    implicitWidth: Math.max(prefixText.implicitWidth, valueText.implicitWidth)
    implicitHeight: prefixText.implicitHeight + valueText.implicitHeight

    Text {
        id: prefixText
        anchors.top: parent.top
        width: root.width
        horizontalAlignment: Text.AlignHCenter
        opacity: enabled ? 1 : 0.33
        color: root.color
        font.bold: true
        font.pixelSize: sizings.fontPixelSize * 0.6
        visible: prefix.length > 0
        text: prefix
    }

    Text {
        id: valueText
        anchors.bottom: parent.bottom
        width: root.width
        horizontalAlignment: Text.AlignHCenter
        opacity: enabled ? 1 : 0.33
        color: root.color
        font.bold: true
        font.pixelSize: sizings.fontPixelSize * 0.75
        text: isNaN(value) ? "-" : value.toFixed(digits)
    }
}

