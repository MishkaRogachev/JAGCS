import QtQuick 2.9

TextInput {
    id: root

    horizontalAlignment: Qt.AlignHCenter
    font.pixelSize: sizings.fontSize
    color: customPalette.textColor
    selectByMouse: true
    selectionColor: customPalette.selectionColor
    selectedTextColor: customPalette.selectedTextColor
    //onActiveFocusChanged: if (activeFocus) selectAll()
}
