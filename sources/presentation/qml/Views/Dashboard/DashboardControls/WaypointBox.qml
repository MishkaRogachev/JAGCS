import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.ComboBox {
    id: control

    property int status: Command.Idle

    currentIndex: -1
    contentColor: status == Command.Idle ? palette.textColor: palette.selectedTextColor
    contentZ: 10
    horizontalAlignment: Text.AlignHCenter
    tipText: qsTr("Go to")

    onActivated: goTo(index)
    onStatusChanged: if (status == Command.Completed || status == Command.Rejected) timer.start()

    function goTo(index) {
        presenter.executeCommand(Command.GoTo, [ index ]);
    }

    Timer {
        id: timer
        onTriggered: status = Command.Idle
    }

    Rectangle {
        anchors.fill: parent
        radius: 3
        color: {
            if (status == Command.Rejected) return palette.dangerColor;
            if (status == Command.Sending) return palette.cautionColor;
            if (status == Command.Completed) return palette.positiveColor;
            return "transparent";
        }
    }
}
