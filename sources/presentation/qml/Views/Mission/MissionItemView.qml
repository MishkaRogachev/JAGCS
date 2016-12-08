import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtPositioning 5.6

import "qrc:/Controls"

Frame {
    id: root

    property real latitude: 0.0
    property real longitude: 0.0
    property real altitude: 0

    ColumnLayout {
        anchors.fill: parent

        // TODO: mission item types
        RowLayout {
            GridLayout {
                columns: 2

                Label {
                    Layout.fillWidth: true
                    text: qsTr("Lat.:")
                }

                SpinBox {
                    Layout.fillWidth: true
                    from: -180
                    to: 180
                    value: latitude
                }

                Label {
                    Layout.fillWidth: true
                    text: qsTr("Lon.:")
                }

                SpinBox {
                    Layout.fillWidth: true
                    from: -180
                    to: 180
                    value: longitude
                }
            }

            Button {
                anchors.verticalCenter: parent.verticalCenter
                iconSource: "qrc:/icons/map-marker.svg"
                // TODO: pick
            }
        }

        RowLayout {
            Label {
                Layout.fillWidth: true
                text: qsTr("Alt.:")
            }

            SpinBox {
                Layout.fillWidth: true
                from: -1000
                to: 20000
                value: altitude
            }
        }
    }
}
