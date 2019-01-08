import QtQuick 2.6
import QtQuick.Layouts 1.3

import Industrial.Controls 1.0 as Controls

Flickable {
    id: menu

    implicitWidth: industrial.baseSize * 7
    contentHeight: contents.height
    boundsBehavior: Flickable.OvershootBounds
    flickableDirection: Flickable.AutoFlickIfNeeded

    Controls.ScrollBar.vertical: Controls.ScrollBar {}

    ColumnLayout {
        id: contents
        spacing: industrial.spacing
        width: parent.width

        Repeater {
            id: repeater
            model: nestedModes

            Controls.Button {
                text: presenter.modeString(modelData)
                iconSource: presenter.modeIcon(modelData)
                flat: true
                contentWidth: width - industrial.baseSize
                implicitWidth: industrial.baseSize * 7
                onClicked: presenter.setMode(modelData)
                Layout.fillWidth: true
            }
        }
    }
}
