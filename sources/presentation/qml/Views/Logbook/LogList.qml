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

    ColumnLayout {
        anchors.fill: parent

        Flickable {
            id: flickable
            Layout.fillWidth: true
            Layout.fillHeight: true
            contentHeight: column.height
            clip: true

            ScrollBar.vertical: Controls.ScrollBar { width: 8 } // TODO: common c++ palette item

            ColumnLayout {
                id: column
                width: flickable.width

                Repeater {
                    model: logs

                    LogEntry {
                        log: modelData
                        Layout.fillWidth: true
                    }
                }
            }
        }

        Controls.Button {
            id: button
            flat: true
            Layout.fillWidth: true
            anchors.bottom: parent.bottom
            iconSource: "qrc:/ui/up.svg"
            onClicked: maximized = false
        }
    }
}
