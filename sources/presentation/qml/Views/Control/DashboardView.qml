import QtQuick 2.6
import QtQuick.Layouts 1.3

ColumnLayout {
    id: root

    property var instruments

    signal instrumentAdded(string name, QtObject view)

    spacing: palette.spacing

    Repeater {
        model: instruments

        Loader {
            Layout.fillWidth: true
            sourceComponent: createIndicator(modelData)
            onItemChanged: if (item) instrumentAdded(modelData, item)
        }
    }

    Item { Layout.fillHeight: true }

    function createIndicator(modelData) {
        switch (modelData) {
        case "af": return Qt.createComponent("Displays/ArtificialHorizon.qml");
        case "fd": return Qt.createComponent("Displays/FlightDisplay.qml");
        case "compas": return Qt.createComponent("Displays/Compass.qml");
        case "hsi": return Qt.createComponent("qrc:/Indicators/SituationIndicator.qml");
        case "status": return Qt.createComponent("Displays/StatusDisplay.qml");
        case "satellite": return Qt.createComponent("Displays/SatelliteDisplay.qml");
        case "nav": return Qt.createComponent("Displays/NavigationDisplay.qml");
        default: return null
        }
    }
}
