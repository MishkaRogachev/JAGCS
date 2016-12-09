import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtPositioning 5.6

import "qrc:/Controls"

Frame {
    id: root

    property real latitude: position.latitude
    property real longitude: position.longitude
    property real altitude: 0

    ColumnLayout {
        anchors.fill: parent

        // TODO: mission item types

        PositionEdit {
            id: position
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
