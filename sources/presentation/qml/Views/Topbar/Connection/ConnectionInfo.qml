import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Popup {
    id: info

    width: sizings.controlBaseSize * 5
    closePolicy: Controls.Popup.CloseOnEscape | Controls.Popup.CloseOnPressOutsideParent

    ColumnLayout {
        anchors.fill: parent
        spacing: sizings.spacing

        Controls.ContentItem {
            iconSource: "qrc:/icons/arrow_down.svg"
            text: qsTr("Recv.:") + " " + bytesRecv.toFixed(1) + " " + qsTr("B/s")
            textColor: customPalette.positiveColor
            font.pixelSize: sizings.secondaryFontSize
            font.bold: true
            Layout.fillWidth: true
        }

        Controls.ContentItem {
            iconSource: "qrc:/icons/arrow_up.svg"
            text: qsTr("Sent:") + " " + bytesSent.toFixed(1) + " " + qsTr("B/s")
            textColor: customPalette.skyColor
            font.pixelSize: sizings.secondaryFontSize
            font.bold: true
            Layout.fillWidth: true
        }

        Controls.Button {
            text: qsTr("Connection")
            onClicked: {
                drawer.setMode(DrawerPresenter.Connection);
                info.close();
            }
            Layout.fillWidth: true
        }
    }
}
