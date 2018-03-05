import QtQuick 2.6

TextInput {
    id: root

    property Item previousItem
    property Item nextItem

    signal decreaseValue()
    signal increaseValue()

    horizontalAlignment: Qt.AlignHCenter
    font.pixelSize: sizings.fontPixelSize
    color: palette.textColor
    selectionColor: palette.selectionColor
    selectedTextColor: palette.selectedTextColor

    onActiveFocusChanged: {
        if (!activeFocus) return;

        selectAll();
        focusedItem = root;
    }

    onEditingFinished: {
        updateValueFromControls();
        if (nextItem && activeFocus) nextItem.forceActiveFocus();
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Left && previousItem && cursorPosition === 0) {
            previousItem.forceActiveFocus();
        }
        else if (event.key === Qt.Key_Right && nextItem && cursorPosition === length) {
            nextItem.forceActiveFocus();
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
