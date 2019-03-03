import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

Item {
    id: vehicleList

    property alias vehicles: list.model
    property alias autoAdd: autoAdd.checked

    onVisibleChanged: drawer.filterEnabled = visible
    Component.onCompleted: drawer.filterEnabled = true

    implicitWidth: industrial.baseSize * 8

    Connections{
        target: drawer
        onFilter: presenter.filter(text)
    }

    VehicleListPresenter {
        id: presenter
        view: vehicleList
    }

    ListView {
        id: list
        anchors.fill: parent
        anchors.margins: industrial.shadowSize
        anchors.bottomMargin: addButton.height
        spacing: industrial.spacing
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

    Controls.BottomBar {
        width: parent.width
        anchors.bottom: parent.bottom

        Controls.CheckBox {
            id: autoAdd
            text: qsTr("Autoadd")
            onCheckedChanged: presenter.setAutoAdd(checked)
        }
    }

    Controls.FloatButton {
        id: addButton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: parent.width / 3
        anchors.bottom: parent.bottom
        highlighted: true
        iconSource: "qrc:/ui/plus.svg"
        tipText: qsTr("Add Vehicle")
        onClicked: presenter.addVehicle()
    }
}
