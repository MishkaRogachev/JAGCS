import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtPositioning 5.6

import "qrc:/Controls"
import "qrc:/JS/helper.js" as Helper

Pane {
    id: root

    property var coordinate: QtPositioning.coordinate();
    height: palette.controlBaseSize

    RowLayout {
        Label {
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: palette.fontPixelSize / 1.5
            Layout.fillWidth: true
            text: qsTr("Lat:") + (coordinate.isValid ?
                                      Helper.degreesToDmsString(
                                          coordinate.latitude, false) :
                                      "-")
        }

        Label {
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: palette.fontPixelSize / 1.5
            Layout.fillWidth: true
            text: qsTr("Lon:") + (coordinate.isValid ?
                                      Helper.degreesToDmsString(
                                          coordinate.longitude, true) :
                                      "-")
        }
    }
}
