import QtQuick 2.9

TextInput {
    id: root

    onActiveFocusChanged: if (activeFocus) selectAll()

    horizontalAlignment: Qt.AlignHCenter
    font.pixelSize: sizings.fontSize
    color: customPalette.textColor
    selectByMouse: true
    selectionColor: customPalette.selectionColor
    selectedTextColor: customPalette.selectedTextColor
}
