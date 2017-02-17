import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtPositioning 5.6

import "qrc:/Controls"
import "qrc:/JS/helper.js" as Helper

Pane {
    id: root

    property var coordinate: QtPositioning.coordinate();

    padding: 0

    RowLayout {

        Button {
            iconSource: "qrc:/icons/layers.svg"
            anchors.verticalCenter: parent.verticalCenter
            onClicked: if (!menu.visible) menu.open()

            Menu {
                id: menu
                y: -parent.height

                MenuItem {
                    text: qsTr("Vehicles")
                    checkable: true
                    checked: map.vehicleVisible
                    onCheckedChanged: map.vehicleVisible = checked
                }
            }
        }

        Label {
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: palette.fontPixelSize / 1.5
            Layout.fillWidth: true
            text: qsTr("Lat:") + (coordinate.isValid ?
                                      Helper.degreesToDmsString(
                                          coordinate.latitude, false) : "-")
        }

        Label {
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: palette.fontPixelSize / 1.5
            Layout.fillWidth: true
            text: qsTr("Lon:") + (coordinate.isValid ?
                                      Helper.degreesToDmsString(
                                          coordinate.longitude, true) : "-")
        }
    }
}
