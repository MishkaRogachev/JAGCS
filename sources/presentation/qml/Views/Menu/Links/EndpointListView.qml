import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

Controls.Frame {
    id: root

    property var endpoints

    signal changed()

    function updateEndpoints(update) {
        repeater.model = endpoints;
        if (update) changed();
    }

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

            Item {
                Layout.minimumWidth: sizings.controlBaseSize
            }
        }

        Repeater {
            id: repeater
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
                onRemove: {
                    endpoints.splice(index, 1);
                    updateEndpoints(true);
                }
                onChanged: {
                    endpoints[index] = endpoint;
                    updateEndpoints(true);
                }
            }
        }

        Controls.Button {
            text: qsTr("Add Link")
            iconSource: "qrc:/icons/add.svg"
            onClicked: {
                endpoints.push("127.0.0.1/8080");
                updateEndpoints(true);
            }
            Layout.fillWidth: true
        }
    }
}
