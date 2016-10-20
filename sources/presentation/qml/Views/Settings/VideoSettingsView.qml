import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Martial"

Frame {
    id: root

    property var sourcesModel

    ColumnLayout{
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true

            Label {
                Layout.fillWidth: true
                text: qsTr("Video source")
            }

            ComboBox {
                Layout.fillWidth: true
                model: sourcesModel
            }
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
