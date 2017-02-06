import QtQuick 2.6

Text {
    id: root

    property string prefix
    property int digits: 0
    property real value

    color: palette.textColor
    wrapMode: Text.WordWrap
    horizontalAlignment: Text.AlignHCenter
    font.bold: true
    font.pixelSize: palette.fontPixelSize * 0.7
    text: prefix + " " + value.toFixed(digits)
}
