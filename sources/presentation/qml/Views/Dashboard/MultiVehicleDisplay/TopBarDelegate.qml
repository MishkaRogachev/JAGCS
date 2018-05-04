import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

RowLayout {
    id: topbarDelegate

    spacing: sizings.spacing

    Controls.Button {
        flat: true
        text: vehicles.showOffline ? qsTr("All vehicles") : qsTr("Online vehicles")
        onClicked: vehicles.showOffline = !vehicles.showOffline
        Layout.preferredWidth: sizings.controlBaseSize * 4
    }

    Controls.Button {
        iconSource: dashboardVisible ? "qrc:/icons/hide_dashboard.svg" :
                                       "qrc:/icons/show_dashboard.svg"
        tipText: (dashboardVisible ? qsTr("Hide") : qsTr("Show")) +
                 " " + qsTr("dashboard")
        flat: true
        onClicked: dashboardVisible = !dashboardVisible
        Layout.alignment: Qt.AlignRight
    }
}
