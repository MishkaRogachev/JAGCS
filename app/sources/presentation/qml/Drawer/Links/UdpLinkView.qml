import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

import "../../Common" as Common

SocketLinkView {
    id: linkView

    viewModel: UdpLinkVm { id: viewModel }

    Common.MvBinding { vm: viewModel; vmProperty: "endpoints"; control: endpointList; property: "endpoints" }
    Common.MvBinding { vm: viewModel; vmProperty: "autoAdd"; control: autoBox; property: "checked" }

    Controls.Label {
        text: qsTr("Setted endpoints")
        horizontalAlignment: Text.AlignHCenter
        Layout.fillWidth: true
    }

    EndpointListView {
        id: endpointList
        Layout.maximumHeight: sizings.controlBaseSize * 6
        Layout.fillWidth: true
    }

    Controls.CheckBox {
        id: autoBox
        text: qsTr("Add endpoint on recv")
        horizontalAlignment: Text.AlignHCenter
        Layout.fillWidth: true
    }
}
