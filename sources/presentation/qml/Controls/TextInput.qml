import QtQuick 2.9

TextInput {
    id: root

    onActiveFocusChanged: if (activeFocus) selectAll()

    horizontalAlignment: Qt.AlignHCenter
    font.pixelSize: sizings.fontPixelSize
    color: palette.textColor
    selectionColor: palette.selectionColor
    selectedTextColor: palette.selectedTextColor
}
