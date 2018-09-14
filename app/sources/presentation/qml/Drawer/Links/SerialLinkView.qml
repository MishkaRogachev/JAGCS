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
        Binding on currentIndex { value: viewModel.baudRates.indexOf(viewModel.baudRate) }
        onActivated: viewModel.setBaudRate(viewModel.baudRates[index])
        Layout.fillWidth: true
    }

    Controls.ComboBox {
        labelText: qsTr("Device")
        model: viewModel.availableDevices
        Binding on currentIndex { value: viewModel.availableDevices.indexOf(viewModel.device); }
        onActivated: viewModel.setDevice(viewModel.availableDevices[index])
        Layout.fillWidth: true
    }
}
