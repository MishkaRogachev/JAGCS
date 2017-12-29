import QtQuick 2.6
import QtQuick.Layouts 1.3

Item {
    id: content

    property color textColor: palette.textColor
    property color iconColor: textColor
    property real iconScaling: 0.6

    property alias iconSource: icon.source
    property alias font: label.font
    property alias text: label.text
    property alias horizontalAlignment: label.horizontalAlignment

    implicitWidth: row.width
    implicitHeight: label.height
    clip: true

    RowLayout {
        id: row
        anchors.centerIn: parent
        spacing: sizings.spacing

        ColoredIcon {
            id: icon
            color: enabled ? iconColor : palette.sunkenColor
            anchors.verticalCenter: parent.verticalCenter
            implicitHeight: content.height * iconScaling
            implicitWidth: height
            visible: source != ""
            Layout.alignment: Qt.AlignHCenter
        }

        Label {
            id: label
            font.pixelSize: sizings.fontPixelSize
            color: enabled ? textColor : palette.sunkenColor
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter
            visible: text.length > 0
            Layout.alignment: Qt.AlignHCenter
        }
    }
}
