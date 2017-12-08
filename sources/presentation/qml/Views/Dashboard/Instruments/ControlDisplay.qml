import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../CommandControls" as CommandControls

BaseDisplay {
    id: controlDisplay

    property int mode: Domain.None
    property var availableModes: []
    property bool armed: false

    ControlDisplayPresenter {
        id: presenter
        view: controlDisplay
    }

    GridLayout {
        anchors.centerIn: parent
        width: parent.width
        columnSpacing: sizings.spacing
        rowSpacing: sizings.spacing
        columns: 2

        CommandControls.Switch {
            text: armed ? qsTr("ARMED") : qsTr("DISARMED")
            tipText: armed ? qsTr("Disarm") : qsTr("Arm")
            enabled: online
            font.pixelSize: sizings.fontPixelSize * 0.75
            font.bold: true
            command: Command.ArmDisarm
            inputChecked: armed
            Layout.fillWidth: true
        }

        CommandControls.ModeBox {
            mode: controlDisplay.mode
            model: availableModes
            tipText: qsTr("Select mode")
            enabled: online
            font.pixelSize: sizings.fontPixelSize * 0.75
            font.bold: true
            Layout.fillWidth: true
        }

        CommandControls.Button {
            tipText: qsTr("Return to launch")
            iconSource: "qrc:/icons/home.svg"
            text: qsTr("RTL")
            command: Command.Return
            enabled: online
            Layout.fillWidth: true
        }
    }
}
