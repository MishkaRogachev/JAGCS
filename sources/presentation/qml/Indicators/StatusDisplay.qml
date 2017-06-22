import QtQuick 2.6
import QtQuick.Layouts 1.3

import "../Controls" as Controls

Item {
    id: root

    property bool online: false
    property bool armed: false
    property string mode: qsTr("None")

    implicitHeight: row.height

    RowLayout {
        id: row
        anchors.centerIn: parent
        width: parent.width

        Controls.Label {
            font.pixelSize: root.width * 0.044
            font.bold: true
            text: armed ? qsTr("ARMED") : qsTr("DISARMED")
            color: online ? palette.textColor : palette.disabledColor
            Layout.alignment: Qt.AlignCenter
        }

        Controls.Label {
            font.pixelSize: root.width * 0.044
            font.bold: true
            text: qsTr("Mode: ") + mode
            color: online ? palette.textColor : palette.disabledColor
            Layout.alignment: Qt.AlignCenter
        }
    }
}
