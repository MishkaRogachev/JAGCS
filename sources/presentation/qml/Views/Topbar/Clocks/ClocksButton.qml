import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../"

TopbarButton {
    id: clocks

    property date currentDateTime

    implicitWidth: clock.implicitWidth
    clickEnabled: false

    ClockPresenter {
        id: presenter
        view: clocks
        Component.onCompleted: start()
    }

    Controls.Label {
        id: clock
        anchors.centerIn: parent
        font.pixelSize: sizings.fontSize * 0.75
        font.bold: true
        text: Qt.formatDateTime(currentDateTime, "ddd MMMM d yyyy - hh:mm:ss")
    }
}
