import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

Controls.Frame {
    id: root

    ColumnLayout {
        anchors.fill: parent

        Repeater {
            model: logs

            LogEntry {
                log: modelData
                Layout.fillWidth: true
            }
        }
    }
}
