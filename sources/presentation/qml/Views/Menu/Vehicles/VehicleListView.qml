import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: vehicleList

    property var vehicleIds: []
    property alias autoAdd: autoAdd.checked

    implicitWidth: palette.controlBaseSize * 11

    VehicleListPresenter {
        id: presenter
        view: vehicleList
        Component.onCompleted: updateVehicles()
    }

    Flickable {
        anchors.fill: parent
        anchors.bottomMargin: addRow.height
        contentHeight: column.height
        clip: true

        Controls.ScrollBar.vertical: Controls.ScrollBar {}

        Controls.Frame {
            visible: repeater.count == 0
            width: parent.width
            height: label.height + palette.margins * 2

            Controls.Label {
                id: label
                text: qsTr("No vehicles present")
                width: parent.width
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
            }
        }

        ColumnLayout {
            id: column
            width: parent.width
            spacing: palette.spacing

            Repeater {
                id: repeater
                model: vehicleIds

                VehicleView {
                    Layout.fillWidth: true
                    vehicleId: modelData
                }
            }
        }
    }

    RowLayout {
        id: addRow
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        spacing: palette.spacing

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
