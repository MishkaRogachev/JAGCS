import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtPositioning 5.6
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../DashboardControls" as DashboardControls

RowLayout {
    id: root

    property int command: Command.UnknownCommand

    property alias tipText: sendButton.tipText

    spacing: sizings.spacing

    Connections {
        target: vehicleDisplay
        onUpdateCommandStatus: if (command == root.command) sendButton.status = status;
    }

    DashboardControls.Label { text: qsTr("Rad. m") }

    Controls.SpinBox {
        id: radiusBox
        to: settings.value("Parameters/maxRadius")
        Layout.fillWidth: true
    }

    DashboardControls.CommandButton {
        id: sendButton
        command: root.command
        iconSource: "qrc:/icons/play.svg"
        args: [ radiusBox.value ]
    }
}
