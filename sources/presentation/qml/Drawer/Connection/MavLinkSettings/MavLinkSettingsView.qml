import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

Controls.Frame {
    id: mavlinkSettings

    property int sysId: 0
    property int compId: 0
    property bool retranslationEnabled: false

    signal setSysId(int sysId);
    signal setCompId(int compId);
    signal setRetranslationEnabled(bool enabled);

    MavLinkSettingPresenter {
        id: presenter
        view: mavlinkSettings
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: industrial.spacing

        Controls.Label {
            text: qsTr("Mavlink protocol settings")
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Controls.SpinBox {
            id: sysIdBox
            labelText: qsTr("System ID")
            from: 0
            to: 255
            flat: true
            Binding on value { value: sysId; when: !sysIdBox.activeFocus }
            onValueModified: setSysId(value)
            Layout.fillWidth: true
        }

        Controls.SpinBox {
            id: compIdBox
            labelText: qsTr("Component ID")
            from: 0
            to: 255
            flat: true
            Binding on value { value: compId; when: !compIdBox.activeFocus }
            onValueModified: setCompId(value)
            Layout.fillWidth: true
        }

        Controls.CheckBox {
            id: retranslationBox
            Binding on checked { value: retranslationEnabled; when: !retranslationBox.activeFocus }
            text: qsTr("Link data retranslation")
            onCheckedChanged: if (activeFocus) setRetranslationEnabled(checked)
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }
    }
}
