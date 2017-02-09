import QtQuick 2.6

Text {
    id: root

    property string prefix
    property string suffix
    property int digits: 0
    property real value
    property bool available: true

    color: available ? palette.textColor : palette.disabledColor
    wrapMode: Text.WordWrap
    horizontalAlignment: Text.AlignHCenter
    font.bold: true
    font.pixelSize: palette.fontPixelSize * 0.7
    text: available ? prefix + " " + value.toFixed(digits) + " " + suffix : "-"
}
