import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

LinkView {
    id: linkView

    viewModel: SerialLinkVm { id: viewModel }

    Controls.ComboBox {
        labelText: qsTr("Baud rate")
        model: viewModel.baudRates
        currentIndex: model.indexOf(viewModel.parameter(LinkDescription.BaudRate))
        onActivated: viewModel.setParameter(LinkDescription.BaudRate, displayText)
        Layout.fillWidth: true
    }

    Controls.ComboBox {
        labelText: qsTr("Device")
        model: viewModel.availableDevices
        currentIndex: model.indexOf(viewModel.parameter(LinkDescription.Device))
        onActivated: viewModel.setParameter(LinkDescription.Device, displayText)
        Layout.fillWidth: true
    }
}
