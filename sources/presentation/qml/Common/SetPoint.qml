import QtQuick 2.6
import QtQuick.Layouts 1.3

import Industrial.Controls 1.0 as Controls

ColumnLayout {
    id: root

    property alias title: titleLabel.text
    property alias latitude: latitudeBox.value
    property alias longitude: longitudeBox.value
    property alias altitude: altitudeBox.value

    signal setPoint(real latitude, real longitude, real altitude)

    spacing: industrial.spacing

    Controls.Label {
        id: titleLabel
        Layout.fillWidth: true
    }

    Controls.CoordSpinBox {
        labelText: qsTr("Lat.")
        id: latitudeBox
        Layout.fillWidth: true
    }

    Controls.CoordSpinBox {
        labelText: qsTr("Lon.")
        id: longitudeBox
        isLongitude: true
        Layout.fillWidth: true
    }

    Controls.RealSpinBox {
        id: altitudeBox
        labelText: qsTr("Alt, m")// TODO: global dimentional units
        realFrom: settings.value("Parameters/minAltitude")
        realTo: settings.value("Parameters/maxAltitude")
        precision: settings.value("Parameters/precisionAltitude")
        Layout.fillWidth: true
    }

    Controls.Button {
        id: button
        text: qsTr("Set point")
        onClicked: setPoint(latitude, longitude, altitude)
        Layout.fillWidth: true
    }
}
