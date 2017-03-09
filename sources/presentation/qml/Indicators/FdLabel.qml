import QtQuick 2.6

Text {
    id: root

    property string prefix
    property string suffix
    property int digits: 0
    property real value
    property bool available: true

    color: available ? palette.textColor : palette.disabledColor
    horizontalAlignment: Text.AlignHCenter
    font.bold: true
    font.pixelSize: root.width * 0.23
    text: available ? (prefix.length > 0 ? prefix + "\n" : "") +
                      value.toFixed(digits) + " " + suffix : "-"
}
