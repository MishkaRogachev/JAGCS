import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

RowLayout {
    id: control

    property alias text: label.text

    Label {
        id: label
        Layout.fillWidth: true
    }

    Controls.ColoredIcon {
        id: icon
        Layout.preferredWidth: sizings.controlBaseSize * 0.5
        Layout.preferredHeight: width
    }

    states: [
        State {
            name: "OK"
            PropertyChanges { target: icon; color: customPalette.positiveColor }
            PropertyChanges { target: icon; source: "qrc:/ui/ok.svg" }
        },
        State {
            name: "BAD"
            PropertyChanges { target: icon; color: customPalette.dangerColor }
            PropertyChanges { target: icon; source: "qrc:/icons/remove.svg" }
        },
        State {
            name: "UNACTIVE"
            PropertyChanges { target: icon; color: customPalette.sunkenColor }
            PropertyChanges { target: icon; source: "qrc:/icons/cancel.svg" }
        },
        State {
            name: "INPROCESS"
            PropertyChanges { target: icon; color: customPalette.highlightColor }
            PropertyChanges { target: icon; source: "qrc:/icons/restore.svg" }
        }
    ]
}
