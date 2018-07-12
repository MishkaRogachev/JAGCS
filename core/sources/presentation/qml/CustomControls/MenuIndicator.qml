import QtQuick 2.6

ColoredIcon {
    id: icon

    property bool focused: false
    property bool opened: false

    width: sizings.controlBaseSize / 2
    height: width
    source: "qrc:/ui/menu_arrow.svg"
    color: {
        if (opened) return customPalette.highlightColor;
        if (focused) return customPalette.selectionColor;
        return customPalette.controlColor;
    }
}
