import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls


Controls.Frame {
    id: joysticAxis

    property string source

    property alias axis: axisBox.currentIndex
    property alias factor: factorBox.value

    GridLayout {
        id: grid
        anchors.fill: parent
        columns: 2
        rowSpacing: sizings.spacing
        columnSpacing: sizings.spacing

        Controls.Label {
            text: source
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Axis")
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            id: axisBox
            model: axes
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Factor")
            Layout.fillWidth: true
        }

        Controls.SpinBox {
            id: factorBox
            //suffix: "%"
            from: -100
            to: 100
            Layout.fillWidth: true
        }
    }
}

