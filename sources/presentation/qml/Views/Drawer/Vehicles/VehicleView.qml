import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Card {
    id: vehicleView

    property int vehicleId: 0
    property bool online: false
    property int type: Vehicle.UnknownType

    property alias name: nameField.text
    property alias mavId: idBox.value
    property alias types: typeBox.model

    onTypeChanged: typeBox.currentIndex = type
    onVehicleIdChanged: presenter.setVehicle(vehicleId)
    // onDeepIn: TODO: edit vehicle
    Component.onCompleted: {
        //menu.addEntry(qsTr("Edit"), "qrc:/icons/edit.svg").triggered.connect(edit);

        var removeItem = menu.addEntry(qsTr("Remove"), "qrc:/icons/remove.svg");
        removeItem.iconColor = customPalette.dangerColor;
        removeItem.triggered.connect(presenter.remove);
    }

    deepEnabled: false
    implicitWidth: grid.implicitWidth + sizings.margins * 2
    implicitHeight: grid.implicitHeight + sizings.margins * 2

    VehiclePresenter {
        id: presenter
        view: vehicleView
    }

    GridLayout {
        id: grid
        anchors.fill: parent
        anchors.margins: sizings.margins
        anchors.rightMargin: vehicleView.margin
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
            onEditingFinished: presenter.rename(text)
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
            isValid: presenter.checkMavId(value)
            onValueModified: presenter.setMavId(value)
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Type:")
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            id: typeBox
            onActivated: presenter.setType(currentIndex)
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
    }
}
