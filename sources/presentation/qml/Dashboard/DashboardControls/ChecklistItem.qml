import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

RowLayout {
    id: control

    property alias text: label.text

    Controls.Label {
        id: label
        Layout.fillWidth: true
    }

    Controls.ColoredIcon {
        id: icon
        Layout.preferredWidth: industrial.baseSize * 0.5
        Layout.preferredHeight: width
    }

    states: [
        State {
            name: "OK"
            PropertyChanges { target: icon; color: industrial.colors.positive }
            PropertyChanges { target: icon; source: "qrc:/ui/ok.svg" }
        },
        State {
            name: "CAUTION"
            PropertyChanges { target: icon; color: industrial.colors.caution }
            PropertyChanges { target: icon; source: "qrc:/icons/info.svg" }
        },
        State {
            name: "BAD"
            PropertyChanges { target: icon; color: industrial.colors.danger }
            PropertyChanges { target: icon; source: "qrc:/icons/remove.svg" }
        },
        State {
            name: "UNACTIVE"
            PropertyChanges { target: icon; color: industrial.colors.background }
            PropertyChanges { target: icon; source: "qrc:/icons/cancel.svg" }
        },
        State {
            name: "INPROCESS"
            PropertyChanges { target: icon; color: industrial.colors.highlight }
            PropertyChanges { target: icon; source: "qrc:/icons/restore.svg" }
        }
    ]
}
