import QtQuick 2.6

QtObject {
    id: palette

    property int controlBaseSize: 36

    property int fontPixelSize: controlBaseSize / 2
    property int controlBaseWidth: controlBaseSize * 6
    property int spacing: controlBaseSize / 4
    property int margins: controlBaseSize / 6

    property color backgroundColor: "#37474F"
    property color sunkenColor: "#263238"
    property color raisedColor: "#455A64"
    property color buttonColor: "#546E7A"

    property color disabledColor: "#212121"

    property color textColor: "#FAFAFA"
    property color selectedTextColor: "#424242"

    property color highlightColor: "#00E676"
    property color selectionColor: "#69F0AE"

    property color negativeColor: "#F44336"
    property color neutralColor: "#FFC107"
    property color positiveColor: "#00E676"
}
