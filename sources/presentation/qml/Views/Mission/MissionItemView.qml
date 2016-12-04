import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtPositioning 5.6

import "qrc:/Controls"

Frame {
    id: root

    property var coordinate

    GridLayout {
        columns: 2
        anchors.fill: parent

        Label {
            Layout.fillWidth: true
            text: qsTr("Lat.:")
        }

        SpinBox {
            Layout.fillWidth: true
            from: -180
            to: 180
            value: coordinate.latitude
        }

        Label {
            Layout.fillWidth: true
            text: qsTr("Lon.:")
        }

        SpinBox {
            Layout.fillWidth: true
            from: -180
            to: 180
            value: coordinate.longitude
        }
    }
}
