import QtQuick 2.6
import QtQuick.Layouts 1.3

Repeater {
    id: root

    property var instruments

    property url vehicleMark
    property bool online: false

    signal instrumentAdded(string name, QtObject view)

    model: instruments

    Loader {
        sourceComponent: createIndicator(modelData)
        onItemChanged: if (item) instrumentAdded(modelData, item)
        enabled: online
        Layout.alignment: Qt.AlignTop
        Layout.minimumHeight: item ? item.minimumHeight : 0
        Layout.maximumHeight: item ? item.maximumHeight : 0
        Layout.preferredHeight: (Layout.minimumHeight + Layout.maximumHeight) / 2
        Layout.fillWidth: true
        Layout.fillHeight: true

        function createIndicator(modelData) {
            switch (modelData) {
            case "satellite": return Qt.createComponent("Displays/SatelliteDisplay.qml");
            case "fd": return Qt.createComponent("Displays/FlightDisplay.qml");
            case "navigator": return Qt.createComponent("Displays/NavigationDisplay.qml");
            case "status": return Qt.createComponent("Displays/StatusDisplay.qml");
            case "mission": return Qt.createComponent("Displays/MissionDisplay.qml");
            default: return null
            }
        }
    }
}
