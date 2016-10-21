import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Martial"

Frame {
    id: root

    property alias sourcesModel: sources.model

    signal sourceSelected(string source)

    function setSource(source) {
        sources.currentIndex = sourcesModel.indexOf(source);
    }


    ColumnLayout{
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true

            Label {
                Layout.fillWidth: true
                text: qsTr("Video source")
            }

            ComboBox {
                id: sources
                Layout.fillWidth: true
                onCurrentTextChanged: sourceSelected(currentText)
            }
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
