import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

Controls.Frame {
    id: root

    padding: palette.margins / 2
    backgroundColor: palette.sunkenColor

    function flickToEnd() {
        flickable.contentY = column.height - flickable.height;
    }

    Flickable {
        id: flickable
        anchors.fill: parent
        contentHeight: column.height
        boundsBehavior: Flickable.StopAtBounds
        clip: true
        ScrollBar.vertical: Controls.ScrollBar {}

        ColumnLayout {
            id: column
            width: root.width

            Repeater {
                model: logs

                LogEntry {
                    log: modelData
                    Layout.fillWidth: true
                }
            }
        }
    }
}
