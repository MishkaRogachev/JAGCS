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
        case "af": return Qt.createComponent("qrc:/Indicators/ArtificialHorizon.qml");
        case "fd": return Qt.createComponent("qrc:/Indicators/FlightDisplay.qml");
        case "compas": return Qt.createComponent("qrc:/Indicators/Compass.qml");
        case "hsi": return Qt.createComponent("qrc:/Indicators/SituationIndicator.qml");
        case "status": return Qt.createComponent("qrc:/Indicators/StatusDisplay.qml");
        case "satellite": return Qt.createComponent("qrc:/Indicators/SatelliteDisplay.qml");
        case "nav": return Qt.createComponent("qrc:/Indicators/NavigationDisplay.qml");
        default: return null
        }
    }
}
