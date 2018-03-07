import QtQuick 2.9

TextInput {
    id: root

    property Item previousItem
    property Item nextItem

    property bool changed: false

    signal decreaseValue()
    signal increaseValue()
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

    onEditingFinished: {
        if (changed) finished();
        if (nextItem && activeFocus) nextItem.forceActiveFocus();
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Left && previousItem && cursorPosition === 0) {
            previousItem.forceActiveFocus();
        }
        else if (event.key === Qt.Key_Right && nextItem && cursorPosition === length) {
            nextItem.forceActiveFocus();
        }
        else if (event.key === Qt.Key_Tab && nextItem ) {
            nextItem.forceActiveFocus();
        }
        else if (event.key === Qt.Key_Backtab && previousItem ) {
            previousItem.forceActiveFocus();
        }
        else if (event.key === Qt.Key_Plus) {
            increaseValue();
        }
        else if (event.key === Qt.Key_Minus) {
            decreaseValue();
        }
        else return;

        event.accepted = true;
    }
}
