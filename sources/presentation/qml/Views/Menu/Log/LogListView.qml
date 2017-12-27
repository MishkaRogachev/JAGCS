import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: logList

    property var logs: []

    implicitWidth: sizings.controlBaseSize * 11

    LogListPresenter {
        id: presenter
        view: logList
        Component.onCompleted: updateLog()
    }

    ListView {
        anchors.fill: parent
        spacing: sizings.spacing
        model: logs

        Controls.ScrollBar.vertical: Controls.ScrollBar {}

        delegate: LogView {
            width: parent.width
            log: modelData
        }
    }
}

