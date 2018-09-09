import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

import "../../Common" as Common

LinkView {
    id: linkView

    Common.MvBinding { vm: provider; vmProperty: "port"; control: portBox; property: "value" }

    Controls.SpinBox {
        id: portBox
        labelText: qsTr("Port")
        from: 0
        to: 65535
        Layout.fillWidth: true
    }
}
