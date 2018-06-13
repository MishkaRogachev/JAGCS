import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Popup {
    id: info

    closePolicy: Controls.Popup.CloseOnEscape | Controls.Popup.CloseOnPressOutsideParent

    ColumnLayout {
        spacing: sizings.spacing

        Controls.ContentItem {
            iconSource: "qrc:/icons/arrow_down.svg"
            text: bytesRecv.toFixed(1) + " " + qsTr("B/s")
            font.pixelSize: sizings.secondaryFontSize
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }

        Controls.ContentItem {
            iconSource: "qrc:/icons/arrow_up.svg"
            text: bytesSent.toFixed(1) + " " + qsTr("B/s")
            font.pixelSize: sizings.secondaryFontSize
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
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
