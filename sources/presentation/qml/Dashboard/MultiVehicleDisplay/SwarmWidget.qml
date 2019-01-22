import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import Industrial.Indicators 1.0 as Indicators

import "../DashboardControls" as DashboardControls

Controls.Pane {
    id: widget

    RowLayout {
        anchors.centerIn: parent
        width: parent.width
        spacing: controlSize.spacing

        DashboardControls.Label {
            text: qsTr("Swarm mode")
            font.pixelSize: controlSize.fontSize
        }
    }
}
