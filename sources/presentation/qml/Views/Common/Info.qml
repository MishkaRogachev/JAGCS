import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls


Controls.Frame {
    id: frame

    property alias message: messageLabel.text

    backgroundColor: customPalette.cautionColor
    visible: message.length > 0
    padding: sizings.padding

    Controls.Label {
        id: messageLabel
        color: customPalette.selectedTextColor
        horizontalAlignment: Text.AlignHCenter
        elide: Text.ElideNone
        wrapMode: Text.WordWrap
        anchors.fill: parent
    }
}
