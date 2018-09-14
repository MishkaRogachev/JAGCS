import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

LinkView {
    id: linkView

    Controls.SpinBox {
        id: portBox
        labelText: qsTr("Port")
        Binding on value { value: viewModel.port; when: !portBox.activeFocus }
        onValueModified: viewModel.setPort(value)
        from: 0
        to: 65535
        Layout.fillWidth: true
    }
}
