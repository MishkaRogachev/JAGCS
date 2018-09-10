import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

LinkView {
    id: linkView

    viewModel: BluetoothLinkVm { id: viewModel }

    Controls.TextField {
        labelText: qsTr("Address")
        text: viewModel.parameter(LinkDescription.Device)
        onTextChanged: changed = true
        Layout.fillWidth: true
    }

    Controls.ComboBox {
        labelText: qsTr("Device")
        model: viewModel.availableDevices
        currentIndex: model.indexOf(viewModel.parameter(LinkDescription.Device))
        onActivated: viewModel.setParameter(LinkDescription.Device, displayText)
        Layout.fillWidth: true
    }

    RowLayout {
            spacing: sizings.spacing

            Controls.Button {
                text: qsTr("Start")
                enabled: !viewModel.discoveringBluetooth
                onClicked: viewModel.startBluetoothDiscovery()
                Layout.fillWidth: true
            }

            Controls.Button {
                text: qsTr("Stop")
                enabled: viewModel.discoveringBluetooth
                onClicked: viewModel.stopBluetoothDiscovery()
                Layout.fillWidth: true
            }
        }
}
