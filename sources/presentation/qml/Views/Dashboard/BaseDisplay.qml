import QtQuick 2.6

Item {
    id: display

    function toggleCentered(vehicleId) {
        map.trackingVehicleId = (map.trackingVehicleId == vehicleId) ? 0 : vehicleId;
    }

    function toggleTracked(vehicleId) {
        if (map.trackingVehicleId == vehicleId)  {
            map.trackYaw = !map.trackYaw;
        } else {
            map.trackingVehicleId = vehicleId;
            map.trackYaw = true;
        }
    }
}
