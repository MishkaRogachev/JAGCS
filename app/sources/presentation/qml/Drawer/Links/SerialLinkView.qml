import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

LinkView {
    id: linkView

    Controls.ComboBox {
        labelText: qsTr("Baud rate")
        model: provider.availableBaudRates
        currentIndex: model.indexOf(provider.parameter(LinkDescription.BaudRate))
        onActivated: provider.setParameter(LinkDescription.BaudRate, displayText)
        Layout.fillWidth: true
    }

    Controls.ComboBox {
        labelText: qsTr("Device")
        model: provider.availableDevices
        currentIndex: model.indexOf(provider.parameter(LinkDescription.Device))
        onActivated: provider.setParameter(LinkDescription.Device, displayText)
        Layout.fillWidth: true
    }
}
