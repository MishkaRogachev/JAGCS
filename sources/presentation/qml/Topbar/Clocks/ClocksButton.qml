import QtQuick 2.6
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
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
        anchors.verticalCenter: parent.verticalCenter
        width: clocks.width
        visible: width > 0
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: industrial.auxFontSize
        font.bold: true
        text: Qt.formatDateTime(currentDateTime, "ddd d MMMM yyyy - hh:mm:ss")
    }
}
