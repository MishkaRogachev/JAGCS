import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

LinkView {
    id: linkView

    Controls.TextField {
        labelText: qsTr("Address")
        text: provider.parameter(LinkDescription.Device)
        onTextChanged: changed = true
        Layout.fillWidth: true
    }

    Controls.ComboBox {
        labelText: qsTr("Device")
        model: provider.availableDevices
        currentIndex: model.indexOf(provider.parameter(LinkDescription.Device))
        onActivated: provider.setParameter(LinkDescription.Device, displayText)
        Layout.fillWidth: true
    }

    RowLayout {
            spacing: sizings.spacing

            Controls.Button {
                text: qsTr("Start")
                enabled: !provider.discoveringBluetooth
                onClicked: provider.startBluetoothDiscovery()
                Layout.fillWidth: true
            }

            Controls.Button {
                text: qsTr("Stop")
                enabled: provider.discoveringBluetooth
                onClicked: provider.stopBluetoothDiscovery()
                Layout.fillWidth: true
            }
        }
}
