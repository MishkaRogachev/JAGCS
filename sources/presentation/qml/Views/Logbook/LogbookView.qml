import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: root

    property bool maximized: false
    property real logHeightFactor: 0.5
    property var logs: []

    LogList {
        width: parent.width
        anchors.top: parent.top
        anchors.topMargin: sizings.margins
        height: maximized ? main.height * logHeightFactor : root.height
        visible: maximized
        onVisibleChanged: if (visible) flickToEnd()
        Behavior on height { PropertyAnimation { duration: 100 } }
    }

    LogEntry {
        width: parent.width
        anchors.verticalCenter: parent.verticalCenter
        log: logs.length > 0 ? logs[logs.length - 1] : null
        visible: !maximized

        MouseArea {
            anchors.fill: parent
            onPressed: maximized = true
        }
    }
}
