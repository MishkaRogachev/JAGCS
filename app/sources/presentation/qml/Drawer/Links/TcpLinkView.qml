import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

SocketLinkView {
    id: linkView

    Controls.TextField {
        labelText: qsTr("Address")
        text: provider.parameter(LinkDescription.Address)
        onEditingFinished: provider.setParameter(LinkDescription.Address, value)
        Layout.fillWidth: true
    }
}
