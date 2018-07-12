import QtQuick 2.6
import QtQuick.Templates 2.2 as T

T.TextField {
    id: control

    property alias labelText: background.text

    implicitWidth: background.implicitWidth
    implicitHeight: background.implicitHeight
    font.pixelSize: sizings.fontSize
    color: customPalette.textColor
    selectionColor: customPalette.selectionColor
    selectedTextColor: customPalette.selectedTextColor
    selectByMouse: true
    leftPadding: sizings.padding
    bottomPadding: background.offset
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignBottom
    opacity: enabled ? 1 : 0.33

    background: BackgroundItem {
        id: background
        anchors.fill: parent
        inputed: displayText.length > 0 || control.activeFocus
        highlighted: control.activeFocus
    }
}
