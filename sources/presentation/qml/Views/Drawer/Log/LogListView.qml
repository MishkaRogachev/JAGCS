import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: logList

    property alias logs: list.model

    implicitWidth: sizings.controlBaseSize * 10

    LogListPresenter {
        id: presenter
        view: logList
        Component.onCompleted: updateLog()
    }

    ListView {
        id: list
        anchors.fill: parent
        spacing: sizings.spacing
        boundsBehavior: Flickable.OvershootBounds
        flickableDirection: Flickable.AutoFlickIfNeeded
        onCountChanged: positionViewAtEnd()

        Controls.ScrollBar.vertical: Controls.ScrollBar {}

        delegate: LogView {
            width: parent.width
            log: modelData
        }
    }
}

