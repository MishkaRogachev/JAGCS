import QtQuick 2.6

QtObject {
    id: palette

    property int controlBaseSize: 36

    property int fontPixelSize: controlBaseSize / 2
    property int spacing: controlBaseSize / 4
    property int margins: controlBaseSize / 4

    property color backgroundColor: "#33454f"
    property color sunkenColor: "#213038"
    property color raisedColor: "#405964"
    property color buttonColor: "#597b8b"

    property color disabledColor: "#212121"

    property color textColor: "#FAFAFA"
    property color selectedTextColor: "#424242"

    property color highlightColor: "#00E676"
    property color selectionColor: "#69F0AE"

    property color negativeColor: "#F44336"
    property color neutralColor: "#FFC107"
    property color positiveColor: "#00E676"
}
