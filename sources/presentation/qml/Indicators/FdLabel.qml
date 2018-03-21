import QtQuick 2.6

Item {
    id: root

    property string prefix
    property int digits: 0
    property real value: 0
    property bool operational: true

    implicitWidth: Math.max(defText.implicitWidth, valueText.implicitWidth)
    implicitHeight: defText.implicitHeight + valueText.implicitHeight

    Text {
        id: defText
        anchors.top: parent.top
        width: root.width
        horizontalAlignment: Text.AlignHCenter
        opacity: enabled ? 1 : 0.33
        color: operational ? customPalette.textColor : customPalette.dangerColor
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
        color: operational ? customPalette.textColor : customPalette.dangerColor
        font.bold: true
        font.pixelSize: sizings.fontPixelSize * 0.75
        text: enabled ? value.toFixed(digits) : "-"
    }
}

