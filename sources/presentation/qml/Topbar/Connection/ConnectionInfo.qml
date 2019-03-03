import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import Industrial.Indicators 1.0 as Indicators

Controls.Popup {
    id: info

    closePolicy: Controls.Popup.CloseOnEscape | Controls.Popup.CloseOnPressOutsideParent

    GridLayout {
        anchors.fill: parent
        columns: 2
        rowSpacing: industrial.spacing

        Controls.Led {
            color: recv ? industrial.colors.positive : industrial.colors.background
        }

        Controls.Label {
            text: qsTr("Recv") + ": " + bytesRecv.toFixed(1) + " " + qsTr("B/s")
            color: industrial.colors.positive
            font.pixelSize: industrial.auxFontSize
            font.bold: true
            Layout.fillWidth: true
        }

        Controls.Led {
            color: sent ? Indicators.Theme.skyColor : industrial.colors.background
        }

        Controls.Label {
            text: qsTr("Sent") + ": " + bytesSent.toFixed(1) + " " + qsTr("B/s")
            color: industrial.colors.neutral
            font.pixelSize: industrial.auxFontSize
            font.bold: true
            Layout.fillWidth: true
        }

        Controls.Button {
            text: qsTr("Open connection menu")
            flat: true
            font.pixelSize: industrial.auxFontSize
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
