import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import Industrial.Indicators 1.0 as Indicators

Controls.ComboBox {
    id: control

    property int status: Command.Idle

    enabled: waypointCount > 0 && vehicle.online
    currentIndex: -1
    labelText: qsTr("Waypoint")
    font.pixelSize: industrial.auxFontSize
    font.bold: true
    contentColor: status == Command.Idle ? industrial.colors.onSurface: industrial.colors.selection
    labelColor: {
        if (!enabled) return industrial.colors.disabled;
        return status == Command.Idle ? industrial.colors.onSurface : industrial.colors.onHighlight;
    }
    backgroundColor: {
        if (status == Command.Rejected) return Indicators.Theme.dangerColor;
        if (status == Command.Sending) return Indicators.Theme.cautionColor;
        if (status == Command.Completed) return Indicators.Theme.positiveColor;
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
