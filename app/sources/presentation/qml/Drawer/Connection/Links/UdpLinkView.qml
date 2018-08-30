import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import Industrial.Indicators 1.0 as Indicators

BaseLinkView {
    id: linkView

    Controls.SpinBox {
        labelText: qsTr("Port")
        from: 0
        to: 65535
        onValueChanged: changed = true
        Layout.fillWidth: true
    }

    Controls.Label {
        text: qsTr("Setted endpoints")
        visible: type == LinkDescription.Udp
        horizontalAlignment: Text.AlignHCenter
        Layout.fillWidth: true
    }

    EndpointListView {
        id: endpointList
        visible: type == LinkDescription.Udp
        onChanged: linkEditView.changed = true;
        Layout.maximumHeight: sizings.controlBaseSize * 6
        Layout.fillWidth: true
    }

    Controls.CheckBox {
        id: autoResponseBox
        text: qsTr("Autoresponse on get data")
        visible: type == LinkDescription.Udp
        horizontalAlignment: Text.AlignHCenter
        onCheckedChanged: changed = true
        Layout.fillWidth: true
    }
}
