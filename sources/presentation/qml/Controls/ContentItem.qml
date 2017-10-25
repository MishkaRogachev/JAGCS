import QtQuick 2.6

Item {
    id: content

    property color iconColor: palette.textColor
    property color textColor: palette.textColor

    property alias iconSource: icon.source
    property alias font: label.font
    property alias text: label.text
    property alias horizontalAlignment: label.horizontalAlignment

    clip: true
    implicitWidth: icon.implicitWidth + label.implicitWidth + palette.spacing
    implicitHeight: Math.max(icon.implicitHeight, label.implicitHeight)

    Row {
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
            verticalAlignment: Text.AlignVCenter
            visible: label.width < content.width - palette.spacing - icon.width
        }
    }
}
