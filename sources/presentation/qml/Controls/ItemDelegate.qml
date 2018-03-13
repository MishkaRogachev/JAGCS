import QtQuick 2.6
import QtQuick.Templates 2.2 as T
import QtQuick.Layouts 1.3

T.ItemDelegate {
    id: control

    property alias horizontalAlignment: content.horizontalAlignment
    property alias iconSource: content.iconSource

    font.pixelSize: sizings.fontPixelSize
    implicitWidth: content.implicitWidth
    implicitHeight: sizings.controlBaseSize
    padding: sizings.padding

    background: Rectangle {
        visible: control.highlighted
        color: palette.selectionColor
        anchors.fill: parent
    }

    contentItem: ContentItem {
        id: content
        font: control.font
        text: control.text
        textColor: control.highlighted ? palette.selectedTextColor : palette.textColor
    }
}
