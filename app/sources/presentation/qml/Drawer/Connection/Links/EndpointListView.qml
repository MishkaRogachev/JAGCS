import QtQuick 2.6
import QtQuick.Layouts 1.3

import Industrial.Controls 1.0 as Controls

Controls.Frame {
    id: root

    property string endpoints

    property var _endpoints: []

    signal changed(string endpoints)

    function updateEndpoints(update) {
        repeater.model = _endpoints;
        if (update) changed(_endpoints.join(";"));
    }

    onEndpointsChanged: {
        _endpoints = endpoints.split(";");
        updateEndpoints(false);
    }

    padding: sizings.padding
    implicitWidth: column.implicitWidth + padding * 2
    implicitHeight: column.height + padding * 2
    backgroundColor: customPalette.sunkenColor

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
                model: _endpoints

                EndpointView {
                    endpoint: modelData
                    onRemove: {
                        _endpoints.splice(index, 1);
                        updateEndpoints(true);
                    }
                    onChanged:{
                        _endpoints[index] = endpoint;
                        updateEndpoints(true);
                    }
                }
            }

            Controls.Button {
                text: qsTr("Add endpoint")
                iconSource: "qrc:/ui/plus.svg"
                onClicked: {
                    _endpoints.push("127.0.0.1:8080");
                    updateEndpoints(true);
                    flickable.toBottom();
                }
                Layout.fillWidth: true
            }
        }
    }
}
