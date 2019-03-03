import QtQuick 2.6
import QtQuick.Layouts 1.3

import Industrial.Controls 1.0 as Controls

Controls.Frame {
    id: frame

    property alias message: messageLabel.text

    backgroundColor: industrial.colors.neutral
    visible: message.length > 0
    padding: industrial.padding

    Controls.Label {
        id: messageLabel
        color: industrial.colors.onSelection
        horizontalAlignment: Text.AlignHCenter
        elide: Text.ElideNone
        wrapMode: Text.WordWrap
        anchors.fill: parent
    }
}
