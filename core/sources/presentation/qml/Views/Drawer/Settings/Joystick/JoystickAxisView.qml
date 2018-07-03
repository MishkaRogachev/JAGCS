import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Frame {
    id: joysticAxis

    property string source

    property alias axis: axisBox.currentIndex
    property alias factor: factorBox.value

    ColumnLayout {
        id: grid
        anchors.fill: parent
        spacing: sizings.spacing

        Controls.Label {
            text: source
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            id: axisBox
            labelText: qsTr("Axis")
            model: axes
            Layout.fillWidth: true
        }

        Controls.SpinBox {
            id: factorBox
            labelText: qsTr("Factor")
            //suffix: "%"
            from: -100
            to: 100
            Layout.fillWidth: true
        }
    }
}

