import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: vehicleList

    property var vehicleIds: []
    property alias autoAdd: autoAdd.checked

    implicitWidth: sizings.controlBaseSize * 11

    VehicleListPresenter {
        id: presenter
        view: vehicleList
        Component.onCompleted: updateVehicles()
    }

    ListView {
        anchors.fill: parent
        anchors.rightMargin: sizings.shadowSize
        anchors.bottomMargin: addRow.height
        spacing: sizings.spacing
        model: vehicleIds

        Controls.ScrollBar.vertical: Controls.ScrollBar {}

        delegate: VehicleView {
            width: parent.width
            vehicleId: modelData
        }

        Controls.Frame {
            visible: parent.count === 0
            width: parent.width
            height: label.height + sizings.margins * 2

            Controls.Label {
                id: label
                text: qsTr("No vehicles present")
                width: parent.width
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

    RowLayout {
        id: addRow
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        spacing: sizings.spacing

        Controls.Button {
            text: qsTr("Add Vehicle")
            iconSource: "qrc:/icons/add.svg"
            onClicked: presenter.addVehicle()
            Layout.fillWidth: true
        }

        Controls.CheckBox {
            id: autoAdd
            text: qsTr("Autoadd")
            onCheckedChanged: presenter.setAutoAdd(checked)
        }
    }
}
