import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

SocketLinkView {
    id: linkView

    viewModel: TcpLinkVm { id: viewModel }

    Controls.TextField {
        id: addressField
        Binding on text { value: viewModel.address; when: !addressField.activeFocus }
        onEditingFinished: viewModel.setAddress(text)
        labelText: qsTr("Address")
        Layout.fillWidth: true
    }
}
