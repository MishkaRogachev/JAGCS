import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

SocketLinkView {
    id: linkView

    viewModel: UdpLinkVm { id: viewModel }

    Controls.Label {
        text: qsTr("Setted endpoints")
        horizontalAlignment: Text.AlignHCenter
        Layout.fillWidth: true
    }

    EndpointListView {
        id: endpointList
        endpoints: viewModel.endpoints
        //onEndpointsChanged: viewModel.setEndpoints(endpoints)
        Layout.maximumHeight: sizings.controlBaseSize * 6
        Layout.fillWidth: true
    }

    Controls.CheckBox {
        id: autoBox
        text: qsTr("Add endpoint on recv")
        checked: viewModel.autoAdd
        onToggled: viewModel.setAutoAdd(checked)
        horizontalAlignment: Text.AlignHCenter
        Layout.fillWidth: true
    }
}
