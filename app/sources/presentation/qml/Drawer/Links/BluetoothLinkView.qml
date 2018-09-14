import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

LinkView {
    id: linkView

    viewModel: BluetoothLinkVm { id: viewModel }

    Controls.TextField {
        id: addressField
        labelText: qsTr("Address")
        Binding on text { value: viewModel.address; when: !addressField.activeFocus }
        onEditingFinished: viewModel.setAddress(text)
        Layout.fillWidth: true
    }

    Controls.ComboBox {
        labelText: qsTr("Device")
        model: viewModel.availableDevices
        Binding on currentIndex { value: viewModel.availableDevices.indexOf(viewModel.device) }
        onActivated: viewModel.setDevice(viewModel.availableDevices[index])
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
