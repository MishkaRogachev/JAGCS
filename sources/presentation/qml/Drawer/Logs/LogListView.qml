import QtQuick 2.6
import QtQuick.Layouts 1.3
import Industrial.Controls 1.0 as Controls
import JAGCS 1.0

Item {
    id: logList

    property var logs: []

    implicitWidth: industrial.baseSize * 11

    LogListPresenter {
        id: presenter
        view: logList
        Component.onCompleted: updateLogs()
    }

    ListView {
        anchors.fill: parent
        spacing: industrial.spacing
        model: logs
        onCountChanged: positionViewAtEnd()

        Controls.ScrollBar.vertical: Controls.ScrollBar {}

        delegate: LogView {
            width: parent.width
            msg: modelData
        }
    }
} 
