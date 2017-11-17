import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

Item {
    id: veh

    property var vehicles
    property alias autoAdd: autoAdd.checked

    signal addVehicle()
    signal setAutoAdd(bool add)

    implicitWidth: palette.controlBaseSize * 11
    Component.onCompleted: factory.createVehiclesPresenter(veh)

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
                text: qsTr("No vehciles present")
                width: parent.width
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
            }
        }

        ColumnLayout {
            id: column
            width: parent.width
            anchors.centerIn: parent
            spacing: palette.spacing

            Repeater {
                id: repeater
                model: vehicles

                VehicleDescriptionView {
                    id: descriptionView
                    Layout.fillWidth: true
                    Component.onCompleted: modelData.setView(descriptionView)
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
            onClicked: addVehicle()
            Layout.fillWidth: true
        }

        Controls.CheckBox {
            id: autoAdd
            text: qsTr("Autoadd")
            onCheckedChanged: setAutoAdd(checked)
        }
    }
}
