import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import Industrial.Indicators 1.0 as Indicators

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
        removeItem.enabled = Qt.binding(function() { return vehicleId > 0 && !online; })
        removeItem.iconColor = industrial.colors.danger;
        removeItem.triggered.connect(presenter.remove);
    }

    deepEnabled: false
    implicitWidth: column.implicitWidth + industrial.margins * 2
    implicitHeight: column.implicitHeight + industrial.margins * 2

    VehiclePresenter {
        id: presenter
        view: vehicleView
    }

    Controls.Led {
        id: led
        anchors.left: column.left
        anchors.top: column.top
        anchors.topMargin: height / 2
        color: online ? industrial.colors.positive : industrial.colors.background
    }

    ColumnLayout {
        id: column
        anchors.fill: parent
        anchors.margins: industrial.margins
        anchors.rightMargin: vehicleView.margin
        spacing: industrial.spacing

        Controls.TextField {
            id: nameField
            labelText: qsTr("Vehicle name")
            onEditingFinished: presenter.rename(text)
            Layout.fillWidth: true
            Layout.leftMargin: led.width + industrial.margins
        }

        Controls.SpinBox {
            id: idBox
            labelText: qsTr("MAVLink identifier")
            enabled: !online
            from: 1
            to: 255
            isValid: presenter.checkMavId(value)
            onValueModified: presenter.setMavId(value)
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            id: typeBox
            labelText: qsTr("Frame type")
            onActivated: presenter.setType(currentIndex)
            Layout.fillWidth: true
        }
    }
}
