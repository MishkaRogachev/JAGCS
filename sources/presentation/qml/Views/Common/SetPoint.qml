import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

GridLayout {
    id: root

    property alias title: titleLabel.text
    property alias latitude: latitudeBox.value
    property alias longitude: longitudeBox.value
    property alias altitude: altitudeBox.value

    signal setPoint(real latitude, real longitude, real altitude)

    columns: 2
    rowSpacing: sizings.spacing
    columnSpacing: sizings.spacing

    Controls.Label {
        id: titleLabel
        Layout.columnSpan: 2
        Layout.fillWidth: true
    }

    Controls.Label { text: qsTr("Lat.") }

    Controls.CoordSpinBox {
        id: latitudeBox
        Layout.fillWidth: true
    }

    Controls.Label { text: qsTr("Lon.") }

    Controls.CoordSpinBox {
        id: longitudeBox
        isLongitude: true
        Layout.fillWidth: true
    }

    Controls.Label { text: qsTr("Alt, m") } // TODO: global dimentional units

    Controls.RealSpinBox {
        id: altitudeBox
        realFrom: settings.value("Parameters/minAltitude")
        realTo: settings.value("Parameters/maxAltitude")
        precision: settings.value("Parameters/precisionAltitude")
        Layout.fillWidth: true
    }

    Controls.Button {
        id: button
        text: qsTr("Set point")
        onClicked: setPoint(latitude, longitude, altitude)
        Layout.columnSpan: 2
        Layout.fillWidth: true
    }
}
