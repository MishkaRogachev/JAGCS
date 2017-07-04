import QtQuick 2.6

Text {
    id: root

    property string prefix
    property string suffix
    property int digits: 0
    property real value: 0
    property bool operational: false

    color: enabled ? (operational ? palette.textColor : palette.negativeColor) :
                     palette.disabledColor
    horizontalAlignment: Text.AlignHCenter
    font.bold: true
    font.pixelSize: root.width * 0.23
    text: (prefix.length > 0 ? prefix + "\n" : "") +
          (enabled ? value.toFixed(digits) + " " + suffix : "-")
}
