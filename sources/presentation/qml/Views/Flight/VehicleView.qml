import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "../../Indicators"

ColumnLayout {
    id: root

    property QtObject vehicle

    FlightDirector {
        id: flightDirector
        Layout.preferredWidth: parent.width

        pitch: vehicle ? vehicle.attitude.pitch : 0.0
        roll: vehicle ? vehicle.attitude.roll : 0.0
        yaw: vehicle ? vehicle.attitude.yaw : 0.0
        velocity: vehicle ? vehicle.trueAirSpeed : 0.0
        altitude: vehicle ? vehicle.barometricAltitude : 0.0
    }
    // TODO: tools

}
