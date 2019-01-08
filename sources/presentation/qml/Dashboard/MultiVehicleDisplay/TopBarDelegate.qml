import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

RowLayout {
    spacing: 0
    height: topbar.height

    Controls.Button {
        flat: true
        visible: dashboardVisible
        font.pixelSize: industrial.auxFontSize
        font.bold: true
        text: vehicles.showOffline ? qsTr("All vehicles") : qsTr("Online vehicles")
        onClicked: vehicles.showOffline = !vehicles.showOffline
        Layout.fillHeight: true
    }

    Controls.Button {
        iconSource: dashboardVisible ? "qrc:/icons/hide_dashboard.svg" :
                                       "qrc:/icons/show_dashboard.svg"
        tipText: (dashboardVisible ? qsTr("Hide") : qsTr("Show")) +
                 " " + qsTr("dashboard")
        flat: true
        onClicked: dashboardVisible = !dashboardVisible
        Layout.fillHeight: true
    }
}
