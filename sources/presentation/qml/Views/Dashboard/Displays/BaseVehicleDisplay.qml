import QtQuick 2.6
import QtPositioning 5.6
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper

Item {
    id: vehicleDisplay

    property int vehicleId: 0
    property string vehicleName
    property int vehicleType: Vehicle.UnknownType
    property bool online: false

    property QtObject presenter: VehicleDisplayPresenter {
        id: presenter
        view: vehicleDisplay
        Component.onCompleted: setVehicle(vehicleId)
    }
}
