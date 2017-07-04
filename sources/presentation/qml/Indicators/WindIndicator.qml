import QtQuick 2.6
import QtQuick.Layouts 1.3

import "../Controls" as Controls

ColumnLayout {
    id: root

    property real direction: 0
    property real speed: 0

    Image {
        source: "qrc:/indicators/wind_mark.svg"
        rotation: direction
        Layout.alignment: Qt.AlignHCenter
    }

    FdLabel {
        Layout.fillWidth: true
        value: speed
        digits: 1
        suffix: qsTr("m/s")
        enabled: true
        operational: true // TODO: wind avability
    }
}
