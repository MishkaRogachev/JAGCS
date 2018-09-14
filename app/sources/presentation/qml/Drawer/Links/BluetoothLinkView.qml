import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

LinkView {
    id: linkView

    viewModel: BluetoothLinkVm { id: viewModel }

    Controls.TextField {
        labelText: qsTr("Address")
        text: viewModel.address
        onEditingFinished: viewModel.setAddress(text)
        Layout.fillWidth: true
    }

    Controls.ComboBox {
        labelText: qsTr("Device")
        model: viewModel.availableDevices
        currentIndex: model.indexOf(viewModel.device)
        onActivated: viewModel.setDevice(currentText)
        Layout.fillWidth: true
    }

    RowLayout {
            spacing: sizings.spacing

            Controls.Button {
                text: qsTr("Start")
                enabled: !viewModel.discoveryActive
                onClicked: viewModel.startBluetoothDiscovery()
                Layout.fillWidth: true
            }

            Controls.Button {
                text: qsTr("Stop")
                enabled: viewModel.discoveryActive
                onClicked: viewModel.stopBluetoothDiscovery()
                Layout.fillWidth: true
            }
        }
}
