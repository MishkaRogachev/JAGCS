import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "./"

RowLayout {
    id: root

    property real latitude: 0.0
    property real longitude: 0.0

    GridLayout {
        columns: 2

        Label {
            Layout.fillWidth: true
            text: qsTr("Lat.:")
        }

        CoordSpinBox {
            Layout.fillWidth: true
            value: latitude
            onValueChanged: latitude = value;
            width: 240
        }

        Label {
            Layout.fillWidth: true
            text: qsTr("Lon.:")
        }

        CoordSpinBox {
            Layout.fillWidth: true
            value: longitude
            onValueChanged: longitude = value;
            isLongitude: true
            width: 240
        }
    }

    Button {
        id: pickButton
        anchors.verticalCenter: parent.verticalCenter
        iconSource: "qrc:/icons/map-marker.svg"
        checkable: true
        // TODO: ask map stop/start picking
    }

    Connections {
            target: map
            onPicked: {
                if (!pickButton.checked) return;
                root.latitude = latitude;
                root.longitude = longitude;
                pickButton.checked = false;
            }
        }
}
