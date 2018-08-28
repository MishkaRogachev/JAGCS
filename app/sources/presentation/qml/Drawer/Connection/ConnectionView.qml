import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

import "Links"

Item {
    id: connection

    implicitWidth: sizings.controlBaseSize * 10

    LinkListView {
        anchors.fill: parent
    }
}
