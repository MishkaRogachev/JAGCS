import QtQuick 2.6

Item {
    id: content
    implicitWidth: row.width
    implicitHeight: row.height

    property color iconColor: palette.textColor
    property color textColor: palette.textColor

    property alias font: label.font
    property alias text: label.text
    property alias iconSource: icon.source

    Row {
        id: row
        anchors.centerIn: parent
        spacing: palette.spacing

        ColoredIcon {
            id: icon
            color: enabled ? iconColor : palette.sunkenColor
            anchors.verticalCenter: parent.verticalCenter
            height: content.height * 0.6
            width: height
            visible: source != ""
        }

        Label {
            id: label
            font.pixelSize: palette.fontPixelSize
            color: enabled ? textColor : palette.sunkenColor
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
