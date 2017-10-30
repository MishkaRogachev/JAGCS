import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../Command"

BaseDisplay {
    id: root

    property int mode: Domain.None
    property var availableModes: []
    property bool armed: false

    implicitHeight: row.height

    RowLayout {
        id: row
        anchors.centerIn: parent
        width: parent.width

        CommandSwitch {
            text: armed ? qsTr("ARMED") : qsTr("DISARMED")
            tipText: armed ? qsTr("Disarm") : qsTr("Arm")
            enabled: online
            font.pixelSize: palette.fontPixelSize * 0.75
            font.bold: true
            command: Command.ArmDisarm
            inputChecked: armed
        }

        CommandModeBox {
            mode: root.mode
            model: availableModes
            tipText: qsTr("Select mode")
            enabled: online
            font.pixelSize: palette.fontPixelSize * 0.75
            font.bold: true
            Layout.alignment: Qt.AlignRight
        }

        CommandButton {
            tipText: qsTr("Return to launch")
            iconSource: "qrc:/icons/home.svg"
            command: Command.Return
            enabled: online
            Layout.alignment: Qt.AlignRight
        }
    }
}
