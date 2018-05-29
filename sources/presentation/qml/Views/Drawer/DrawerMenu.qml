import QtQuick 2.6
import QtQuick.Layouts 1.3

import "../../Controls" as Controls

ColumnLayout {
    id: menu

    property alias menuModel: repeater.model

    spacing: sizings.spacing

    Repeater {
        id: repeater

        Controls.Button {
            text: presenter.modeString(modelData)
            iconSource: presenter.modeIcon(modelData)
            flat: true
            contentWidth: width - sizings.controlBaseSize
            implicitWidth: sizings.controlBaseSize * 7
            onClicked: presenter.setMode(modelData)
            Layout.fillWidth: true
        }
    }
}
