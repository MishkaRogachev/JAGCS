import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

Controls.ComboBox {
    id: control

    property int status: Command.Idle

    enabled: waypointCount > 0 && vehicle.online
    currentIndex: -1
    labelText: qsTr("Waypoint")
    font.pixelSize: industrial.auxFontSize
    font.bold: true
    contentColor: status == Command.Idle ? industrial.colors.onSurface: industrial.colors.selectedTextColor
    backgroundColor: {
        if (status == Command.Rejected) return industrial.colors.danger;
        if (status == Command.Sending) return industrial.colors.caution;
        if (status == Command.Completed) return industrial.colors.positive;
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
