import QtQuick 2.9

NumericInput {
    id: root

    property Item previousItem
    property Item nextItem

    signal decreaseValue()
    signal increaseValue()

    onFinished: updateValueFromControls()
    onEditingFinished: if (nextItem && activeFocus) nextItem.forceActiveFocus()
    onActiveFocusChanged: if (activeFocus) focusedItem = root

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
