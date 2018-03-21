import QtQuick 2.6

Text {
    id: root

    property string prefix
    property string suffix
    property int digits: 0
    property real value: 0
    property bool operational: true

    opacity: enabled ? 1 : 0.33
    color: operational ? palette.textColor : palette.dangerColor
    horizontalAlignment: Text.AlignHCenter
    font.bold: true
    font.pixelSize: sizings.fontPixelSize * 0.6
    wrapMode: Text.WordWrap
    text: (prefix.length > 0 ? prefix + "\n" : "") +
          (enabled ? value.toFixed(digits) + " " + suffix : "-")
}

