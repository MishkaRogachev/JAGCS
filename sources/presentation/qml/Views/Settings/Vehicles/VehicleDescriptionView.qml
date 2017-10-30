import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Frame {
    id: root

    property bool online: false
    property bool changed: false
    property int type: Vehicle.UnknownType

    property alias name: nameField.text
    property alias mavId: idBox.value
    property alias types: typeBox.model

    signal save()
    signal restore()
    signal remove()

    onTypeChanged: typeBox.currentIndex = type

    GridLayout {
        anchors.fill: parent
        columns: 4
        rowSpacing: palette.spacing

        Controls.Label {
            text: qsTr("Name:")
            Layout.fillWidth: true
        }

        Controls.TextField {
            id: nameField
            placeholderText: qsTr("Enter name")
            onEditingFinished: changed = true
            Layout.fillWidth: true
            Layout.columnSpan: 2
        }

        Controls.Button {
            tipText: qsTr("Save")
            iconSource: "qrc:/icons/save.svg"
            onClicked: save()
            enabled: changed
        }

        Controls.Label {
            text: qsTr("MAV Id:")
            Layout.fillWidth: true
        }

        Controls.SpinBox {
            id: idBox
            enabled: !online
            from: 0
            to: 255
            onValueChanged: changed = true
            Layout.fillWidth: true
            Layout.columnSpan: 2
        }

        Controls.Button {
            tipText: qsTr("Restore")
            iconSource: "qrc:/icons/restore.svg"
            onClicked: restore()
            enabled: changed
        }

        Controls.Label {
            text: qsTr("Type:")
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            id: typeBox
            onCurrentIndexChanged: {
                type = currentIndex;
                changed = true;
            }
            Layout.fillWidth: true
            Layout.columnSpan: 2
        }

        Controls.DelayButton {
            tipText: qsTr("Remove")
            iconSource: "qrc:/icons/remove.svg"
            onActivated: remove()
            enabled: !online
            iconColor: palette.dangerColor
        }

        Controls.Label {
            text: qsTr("Status:")
            Layout.fillWidth: true
        }

        Controls.Label {
            text: online ? qsTr("Online") : qsTr("Offline")
            Layout.fillWidth: true
            Layout.columnSpan: 3
        }
    }
}
