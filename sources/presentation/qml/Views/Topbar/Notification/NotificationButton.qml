import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../"

TopbarButton {
    id: notification

    clickEnabled: false

    Controls.ColoredIcon {
        anchors.centerIn: parent
        source: "qrc:/icons/info.svg"
        color: clickEnabled ? customPalette.textColor : customPalette.sunkenColor
    }

    NotificationListView {
        id: list
        y: parent.height + sizings.margins
        visible: count > 0
    }


}
