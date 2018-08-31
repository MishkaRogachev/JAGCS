import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

BaseLinkEditView {
    id: linkView

    Controls.SpinBox {
        labelText: qsTr("Port")
        from: 0
        to: 65535
        value: presenter.parameter(LinkDescription.Port)
        onValueModified: presenter.setParameter(LinkDescription.Port, value)
        Layout.fillWidth: true
    }

    Controls.Label {
        text: qsTr("Setted endpoints")
        horizontalAlignment: Text.AlignHCenter
        Layout.fillWidth: true
    }

    EndpointListView {
        id: endpointList
        onChanged: linkEditView.changed = true
        Layout.maximumHeight: sizings.controlBaseSize * 6
        Layout.fillWidth: true
    }

    Controls.CheckBox {
        id: autoResponseBox
        text: qsTr("Autoresponse on get data")
        horizontalAlignment: Text.AlignHCenter
        checked: presenter.parameter(LinkDescription.UdpAutoResponse)
        onToggled: presenter.setParameter(LinkDescription.UdpAutoResponse, toggled)
        Layout.fillWidth: true
    }
}
