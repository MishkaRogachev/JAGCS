import QtQuick 2.6
import QtQuick.Controls 2.0

import "qrc:/Controls"

Grid {
    columns: 2

    Label {
        text: qsTr("Item")
        font.bold: true
    }

    ComboBox {
        id: selectedItemBox
        model: vehicle ? vehicle.missionItems : []
        enabled: vehicle
    }

    Button {
        iconSource: "qrc:/icons/play.svg"
        onClicked: vehicle.commandJumpTo(selectedItemBox.currentText)
        enabled: vehicle
    }

    Button {
        iconSource: "qrc:/icons/home.svg"
        onClicked: vehicle.commandReturn()
        enabled: vehicle
    }
}
