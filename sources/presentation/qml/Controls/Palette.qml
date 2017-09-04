import QtQuick 2.6

QtObject {
    id: palette

    property int controlBaseSize: 36

    property int fontPixelSize: controlBaseSize / 2
    property int spacing: controlBaseSize / 4
    property int margins: controlBaseSize / 4

    property color backgroundColor
    property color sunkenColor
    property color raisedColor
    property color buttonColor

    property color textColor
    property color selectedTextColor

    property color highlightColor
    property color selectionColor

    property color dangerColor
    property color cautionColor
    property color positiveColor
}
