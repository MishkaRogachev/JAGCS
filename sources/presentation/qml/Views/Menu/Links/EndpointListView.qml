import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

Controls.Frame {
    id: root

    property var endpoints

    backgroundColor: palette.sunkenColor

    ColumnLayout {
        anchors.fill: parent
        spacing: sizings.spacing

        RowLayout {
            spacing: sizings.spacing

            Controls.Label {
                text: qsTr("Address")
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
            }

            Controls.Label {
                text: qsTr("Port")
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
            }
        }

        Repeater {
            model: root.endpoints

            RowLayout {
                spacing: sizings.spacing

                Controls.Label {
                    text: qsTr("Address")
                    horizontalAlignment: Text.AlignHCenter
                    Layout.fillWidth: true
                }

                Controls.Label {
                    text: qsTr("Port")
                    horizontalAlignment: Text.AlignHCenter
                    Layout.fillWidth: true
                }
            }

            EndpointView {
                endpoint: modelData
                onRemove: endpoints.remove(index)
            }
        }
    }
}
