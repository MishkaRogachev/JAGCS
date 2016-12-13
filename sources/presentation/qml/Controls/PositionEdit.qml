import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "./"

RowLayout {
    id: root

    property alias latitude: latitudeEdit.value
    property alias longitude: longitudeEdit.value

    Label {
        Layout.fillWidth: true
        text: qsTr("Lat.:")
    }

    CoordSpinBox {
        id: latitudeEdit
        Layout.fillWidth: true
        width: 240
    }

    Label {
        Layout.fillWidth: true
        text: qsTr("Lon.:")
    }

    CoordSpinBox {
        id: longitudeEdit
        Layout.fillWidth: true
        isLongitude: true
        width: 240
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
