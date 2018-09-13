import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

import "../../Common" as Common

LinkView {
    id: linkView

    viewModel: SerialLinkVm { id: viewModel }

    // FIXME: combobox for MVVM
//    Common.MvBinding { vmProperty: "baudRate"; control: baudRateBox; property: "currentModelText" }
//    Common.MvBinding { vmProperty: "device"; control: deviceBox; property: "currentModelText" }


    Controls.ComboBox {
        id: baudRateBox
        labelText: qsTr("Baud rate")
        model: viewModel.baudRates
        Layout.fillWidth: true
    }

    Controls.ComboBox {
        id: deviceBox
        labelText: qsTr("Device")
        model: viewModel.availableDevices
        Layout.fillWidth: true
    }
}
