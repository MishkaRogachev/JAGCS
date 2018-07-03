import QtQuick 2.6
import QtQuick.Layouts 1.3

RowLayout {
    id: content

    property color textColor: customPalette.textColor
    property color iconColor: textColor
    property real iconScaling: 0.6

    property alias iconSource: icon.source
    property alias font: label.font
    property alias text: label.text
    property alias horizontalAlignment: label.horizontalAlignment
    property alias verticalAlignment: label.verticalAlignment

    spacing: sizings.spacing

    Item {
        Layout.preferredWidth: icon.width
        Layout.fillHeight: true
        visible: iconSource != ""

        ColoredIcon {
            id: icon
            anchors.centerIn: parent
            width: parent.height * iconScaling
            height: width
            color: enabled ? iconColor : customPalette.sunkenColor
        }
    }

    Text {
        id: label
        font.pixelSize: sizings.fontSize
        color: enabled ? textColor : customPalette.sunkenColor
        verticalAlignment: Text.AlignVCenter
        visible: text.length > 0
        Layout.alignment: Qt.AlignVCenter
        Layout.fillWidth: true
        Layout.fillHeight: true
    }
}
