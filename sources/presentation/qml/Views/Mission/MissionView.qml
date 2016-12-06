import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

Pane {
    id: root

    property var missionNames
    property var missionItems

    signal missionSelected(string name)

    MissionMapView {
        objectName: "map"
        anchors.fill: parent
    }

    ColumnLayout {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 7

        RowLayout {
            ComboBox {
                model: missionNames
                onCurrentTextChanged: missionSelected(currentText)
            }

            Button {
                iconSource: "qrc:/icons/download.svg"
            }

            Button {
                iconSource: "qrc:/icons/upload.svg"
            }
        }

        ListView {
            Layout.fillHeight: true

            Repeater {
                model: missionItems
                onModelChanged: console.log(model)

                MissionItemView {
                    height: 128
                }
            }
        }
    }
}
