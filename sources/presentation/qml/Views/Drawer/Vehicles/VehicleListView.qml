import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: vehicleList

    property alias vehicles: list.model
    property alias autoAdd: autoAdd.checked

    implicitWidth: sizings.controlBaseSize * 10

    VehicleListPresenter {
        id: presenter
        view: vehicleList
    }

    ListView {
        id: list
        anchors.fill: parent
        anchors.margins: sizings.shadowSize
        anchors.bottomMargin: addButton.height
        spacing: sizings.spacing
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds

        Controls.ScrollBar.vertical: Controls.ScrollBar {
            visible: parent.contentHeight > parent.height
        }

        delegate: VehicleView {
            width: parent.width
            vehicleId: model.vehicleId
        }
    }

    Controls.Label {
        anchors.centerIn: parent
        text: qsTr("No vehicles present")
        visible: list.count === 0
    }

    Rectangle { // TODO: bottom navigation bar control
        width: parent.width
        height: sizings.controlBaseSize
        color: customPalette.sunkenColor
        anchors.bottom: parent.bottom

        Controls.CheckBox {
            id: autoAdd
            text: qsTr("Autoadd")
            onCheckedChanged: presenter.setAutoAdd(checked)
        }
    }

    Controls.RoundButton {
        id: addButton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: parent.width / 3
        anchors.bottom: parent.bottom
        iconSource: "qrc:/icons/add.svg"
        tipText: qsTr("Add Vehicle")
        onClicked: presenter.addVehicle()
    }
}
