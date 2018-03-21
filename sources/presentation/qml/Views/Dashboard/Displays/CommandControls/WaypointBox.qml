import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.ComboBox {
    id: control

    property int status: Command.Idle

    currentIndex: -1
    contentColor: status == Command.Idle ? customPalette.textColor: customPalette.selectedTextColor
    contentZ: 10
    horizontalAlignment: Text.AlignHCenter
    tipText: qsTr("Go to mission item")
    font.pixelSize: sizings.fontPixelSize * 0.75
    font.bold: true

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
            if (status == Command.Rejected) return customPalette.dangerColor;
            if (status == Command.Sending) return customPalette.cautionColor;
            if (status == Command.Completed) return customPalette.positiveColor;
            return "transparent";
        }
    }
}
