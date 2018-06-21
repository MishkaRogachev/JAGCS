import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

Controls.Popup {
    id: info

    closePolicy: Controls.Popup.CloseOnEscape | Controls.Popup.CloseOnPressOutsideParent

    GridLayout {
        anchors.fill: parent
        columns: 2
        rowSpacing: sizings.spacing

        Indicators.Led {
            color: recv ? customPalette.positiveColor : customPalette.sunkenColor
        }

        Controls.Label {
            text: qsTr("Recv") + ": " + bytesRecv.toFixed(1) + " " + qsTr("B/s")
            color: customPalette.positiveColor
            font.pixelSize: sizings.secondaryFontSize
            font.bold: true
            Layout.fillWidth: true
        }

        Indicators.Led {
            color: sent ? customPalette.skyColor : customPalette.sunkenColor
        }

        Controls.Label {
            text: qsTr("Sent") + ": " + bytesSent.toFixed(1) + " " + qsTr("B/s")
            color: customPalette.skyColor
            font.pixelSize: sizings.secondaryFontSize
            font.bold: true
            Layout.fillWidth: true
        }

        Controls.Button {
            text: qsTr("Open connection menu")
            flat: true
            font.pixelSize: sizings.secondaryFontSize
            font.bold: true
            onClicked: {
                drawer.setMode(DrawerPresenter.Connection);
                info.close();
            }
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }
    }
}
