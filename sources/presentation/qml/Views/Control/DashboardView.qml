import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls"

ColumnLayout {
    id: root

    property var instruments

    Repeater {
        model: instruments

        Loader {
            Layout.fillWidth: true
            sourceComponent: createInstrument(modelData)
            onItemChanged: if (item) item.objectName = modelData
        }
    }

    function createInstrument(modelData) {
        switch (modelData) {
        case "af": return Qt.createComponent("Instruments/ArtificialHorizon.qml");
        default: return null
        }
    }
}
