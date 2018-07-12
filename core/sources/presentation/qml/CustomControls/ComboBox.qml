import QtQuick 2.6
import QtQuick.Templates 2.1 as T
import QtQuick.Layouts 1.3

T.ComboBox {
    id: control

    property var currentItem: model && model[currentIndex] ? model[currentIndex] : undefined
    property string iconRole: "icon"
    property string displayIcon: currentItem && currentItem[control.iconRole] !== undefined ?
                                      currentItem[control.iconRole] : ""

    // TODO: move all features to special comboboxes
    property alias labelText: background.text
    property alias labelColor: background.textColor
    property alias backgroundColor: background.color
    property alias contentColor: content.textColor
    property alias horizontalAlignment: content.horizontalAlignment

    implicitWidth: background.implicitWidth
    implicitHeight: background.implicitHeight
    font.pixelSize: sizings.fontSize
    padding: sizings.padding
    opacity: enabled ? 1 : 0.33
    clip: true
    textRole: "text"
    displayText: currentItem && currentItem[control.textRole] !== undefined ?
                     currentItem[control.textRole] : currentItem

    indicator: MenuIndicator {
        x: control.width - width
        y: control.height - height
        focused: control.activeFocus
        opened: control.down
    }

    background: BackgroundItem {
        id: background
        anchors.fill: parent
        inputed: displayText.length > 0
        highlighted: control.activeFocus
    }

    delegate: ItemDelegate {
        width: control.width
        horizontalAlignment: control.horizontalAlignment
        text: modelData[control.textRole] !== undefined ?
                  modelData[control.textRole] : modelData
        iconSource: modelData[control.iconRole] !== undefined ?
                        modelData[control.iconRole] : ""
        font: control.font
        highlighted: control.highlightedIndex === index
    }

    contentItem: ContentItem {
        id: content
        anchors.fill: parent
        anchors.bottomMargin: background.offset
        font: control.font
        text: displayText
        iconSource: displayIcon
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: labelText.length > 0 ? Text.AlignBottom : Text.AlignVCenter
    }

    popup: Popup {
        y: control.height
        width: control.width
        implicitHeight: contentItem.implicitHeight
        padding: 1

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: control.popup.visible ? control.delegateModel : null
            currentIndex: control.highlightedIndex
            boundsBehavior: Flickable.StopAtBounds
            ScrollBar.vertical: ScrollBar {}
        }
    }
}
