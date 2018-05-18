import QtQuick 2.6

import "./"

Item {
    id: control

    signal deepIn()

    property alias menuEnabled: menuButton.enabled
    property alias menu: menu
    property alias backgroundColor: background.color
    readonly property int margin: menuButton.width

    property Item contentItem: Item {}

    implicitWidth: contentItem.implicitWidth + sizings.margins * 2
    implicitHeight: contentItem.implicitHeight + sizings.margins * 2

    Rectangle {
        id: background
        anchors.fill: control
        color: customPalette.backgroundColor
        radius: 2
        z: -1

        Shadow {
            source: parent
        }
    }

    Button {
        id: menuButton
        anchors.top: parent.top
        anchors.right: parent.right
        iconSource: "qrc:/ui/dots.svg"
        flat: true
        enabled: false
        width: sizings.controlBaseSize * 0.5
        height: sizings.controlBaseSize * 0.75
        onClicked: menu.open()

        Menu {
            id: menu
            y: parent.height

            function addEntry(text, iconSource) {
                var item = menuItem.createObject(null, { text: text, iconSource: iconSource });
                menu.addItem(item);
                menuButton.enabled = true;
                return item;
            }

            Component {
                id: menuItem
                MenuItem {}
            }
        }
    }

    ColoredIcon {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        source: "qrc:/ui/menu_arrow.svg"
        color: {
            if (area.pressed) return customPalette.highlightColor;
            if (area.containsMouse) return customPalette.selectionColor;
            return customPalette.buttonColor
        }

        width: sizings.controlBaseSize * 0.75
        height: width

        MouseArea {
            id: area
            hoverEnabled: true
            anchors.fill: parent
            onClicked: deepIn()
        }
    }
}
