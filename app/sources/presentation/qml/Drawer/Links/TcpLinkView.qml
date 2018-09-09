import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

import "../../Common" as Common

SocketLinkView {
    id: linkView

    Common.MvBinding { vm: provider; vmProperty: "address"; control: addressField; property: "text" }

    Controls.TextField {
        id: addressField
        labelText: qsTr("Address")
        Layout.fillWidth: true
    }
}
