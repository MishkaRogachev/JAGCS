import QtQuick 2.6
import QtQuick.Layouts 1.3

import Industrial.Controls 1.0 as Controls

Controls.Frame {
    id: root

    property var endpoints

    signal changed()

    function updateEndpoints(update) {
        repeater.model = endpoints;
        if (update) changed();
    }

    padding: industrial.padding
    implicitWidth: column.implicitWidth + padding * 2
    implicitHeight: column.height + padding * 2
    backgroundColor: industrial.colors.background

    Flickable {
        id: flickable
        anchors.fill: parent
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds
        contentHeight: column.height
        clip: true

        function toBottom() {
            contentY = contentHeight - height;
        }

        ColumnLayout {
            id: column
            width: parent.width
            spacing: industrial.spacing

            RowLayout {
                spacing: industrial.spacing

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
                    Layout.minimumWidth: industrial.baseSize
                }
            }

            Repeater {
                id: repeater
                model: root.endpoints

                RowLayout {
                    spacing: industrial.spacing

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
                text: qsTr("Add endpoint")
                iconSource: "qrc:/ui/plus.svg"
                onClicked: {
                    endpoints.push("127.0.0.1/8080");
                    updateEndpoints(true);
                    flickable.toBottom();
                }
                Layout.fillWidth: true
            }
        }
    }
}
