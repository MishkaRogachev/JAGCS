import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Frame {
    id: vehicleView

    property int vehicleId: 0
    property bool online: false
    property bool mavIdIsCorrect: false
    property bool changed: false
    property int type: Vehicle.UnknownType

    property alias name: nameField.text
    property alias mavId: idBox.value
    property alias types: typeBox.model

    onTypeChanged: typeBox.currentIndex = type

    VehiclePresenter {
        id: presenter
        view: vehicleView
        Component.onCompleted: setVehicle(vehicleId)
    }

    GridLayout {
        anchors.fill: parent
        columns: 2
        rowSpacing: sizings.spacing
        columnSpacing: sizings.spacing

        Controls.Label {
            text: qsTr("Name:")
            Layout.fillWidth: true
        }

        Controls.TextField {
            id: nameField
            placeholderText: qsTr("Enter name")
            onEditingFinished: changed = true
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("MAV Id:")
            Layout.fillWidth: true
        }

        Controls.SpinBox {
            id: idBox
            enabled: !online
            from: 1
            to: 255
            backgroundColor: mavIdIsCorrect ? palette.sunkenColor : palette.dangerColor
            onValueChanged: {
                presenter.checkMavId(value);
                changed = true;
            }
            Layout.fillWidth: true
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
        }

        Controls.Label {
            text: qsTr("Status")
            Layout.fillWidth: true
        }

        Controls.Label {
            text: online ? qsTr("Online") : qsTr("Offline")
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Actions")
            Layout.fillWidth: true
        }

        RowLayout {
            Controls.Button {
                tipText: qsTr("Save")
                iconSource: "qrc:/icons/save.svg"
                onClicked: presenter.save()
                enabled: mavIdIsCorrect && changed
            }

            Controls.Button {
                tipText: qsTr("Restore")
                iconSource: "qrc:/icons/restore.svg"
                onClicked: presenter.updateView()
                enabled: changed
            }

            Controls.DelayButton {
                tipText: qsTr("Remove")
                iconSource: "qrc:/icons/remove.svg"
                onActivated: presenter.remove()
                enabled: !online
                iconColor: palette.dangerColor
            }
        }
    }
}
