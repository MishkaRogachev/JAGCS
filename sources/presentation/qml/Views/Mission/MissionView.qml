import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

import "../Map"
import "../Video"

Pane {
    id: root

    MapView {
        id: map
        anchors.fill: parent
    }
}
