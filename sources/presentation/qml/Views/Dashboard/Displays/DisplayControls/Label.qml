import QtQuick 2.6

import "qrc:/Controls" as Controls

                Controls.Label {
                    text: translator.translateVehicleMode(vehicle.mode)
                    font.bold: true
                    font.pixelSize: sizings.fontPixelSize * 0.6
                    horizontalAlignment: Text.AlignRight
                    Layout.fillWidth: true
                }