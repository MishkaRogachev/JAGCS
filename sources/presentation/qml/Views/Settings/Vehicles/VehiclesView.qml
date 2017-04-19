import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

ColumnLayout {
    id: root

    property var vehicles

    signal addVehicle()

    Flickable {
        Layout.fillWidth: true
        Layout.fillHeight: true
        contentHeight: column.height
        clip: true

        ScrollBar.vertical: ScrollBar {}

        Frame {
            visible: repeater.count == 0
            width: parent.width
            height: label.height + palette.margins * 2

            Label {
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
                model: links

                Item {
                    // TODO: vehicle view
                }
            }
        }
    }

    Button {
        id: addButton
        Layout.fillWidth: true
        text: qsTr("Add Vehicle")
        iconSource: "qrc:/icons/add.svg"
        anchors.right: parent.right
        onClicked: addVehicle()
    }
}
