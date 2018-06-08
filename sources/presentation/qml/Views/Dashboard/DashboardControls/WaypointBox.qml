import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.ComboBox {
    id: control

    property int status: Command.Idle

    enabled: vehicle.online
    currentIndex: -1
    labelText: qsTr("Waypoint")
    font.pixelSize: sizings.secondaryFontSize
    font.bold: true
    contentColor: status == Command.Idle ? customPalette.textColor: customPalette.selectedTextColor
    backgroundColor: {
        if (status == Command.Rejected) return customPalette.dangerColor;
        if (status == Command.Sending) return customPalette.cautionColor;
        if (status == Command.Completed) return customPalette.positiveColor;
        return "transparent";
    }

    onActivated: goTo(index)
    onStatusChanged: if (status == Command.Completed || status == Command.Rejected) timer.start()

    function goTo(index) {
        presenter.executeCommand(Command.GoTo, [ index ]);
    }

    Timer {
        id: timer
        onTriggered: status = Command.Idle
    }
}
