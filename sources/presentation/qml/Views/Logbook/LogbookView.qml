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
        anchors.left: parent.left
        anchors.right: button.left
        anchors.top: parent.top
        height: maximized ? main.height * logHeightFactor : root.height
        visible: maximized
        onVisibleChanged: if (visible) flickToEnd();
        Behavior on height { PropertyAnimation { duration: 100 } }
    }

    LogEntry {
        anchors.left: parent.left
        anchors.right: button.left
        anchors.verticalCenter: parent.verticalCenter
        log: logs.length > 0 ? logs[logs.length - 1] : null
        visible: !maximized
        clip: true
    }

    Controls.Button {
        id: button
        flat: true
        anchors.right: parent.right
        anchors.top: parent.top
        iconSource: maximized ? "qrc:/ui/up.svg" : "qrc:/ui/down.svg"
        onClicked: maximized = !maximized
    }
}
