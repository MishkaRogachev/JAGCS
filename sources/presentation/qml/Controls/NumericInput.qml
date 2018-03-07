import QtQuick 2.9

TextInput {
    id: root

    property bool changed: false

    signal finished()

    horizontalAlignment: Qt.AlignHCenter
    font.pixelSize: sizings.fontPixelSize
    color: palette.textColor
    selectionColor: palette.selectionColor
    selectedTextColor: palette.selectedTextColor

    onFinished: changed = false
    onTextEdited: changed = true
    onActiveFocusChanged: {
        if (activeFocus) selectAll();
        else if (changed) finished();
    }

    onEditingFinished: if (changed) finished()
}
