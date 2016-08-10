import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "../Common"

Item {
    id: root

    RowLayout {
        anchors.fill: parent
        anchors.margins: 5

        ColumnLayout {
            id: toolsColumn
            Layout.fillHeight: true
            Layout.preferredWidth: 256

            // TODO: tools

            Item {
                width: 1
                Layout.fillHeight: true
            }

            Loader {
                id: auxiliaryWorkspace
                Layout.preferredWidth: 320
                Layout.preferredHeight: width * 3 / 4
                sourceComponent: videoComponent

                Button {
                    anchors.top: parent.top
                    anchors.right: parent.right
                    text: qsTr("Switch")
                    z: 1
                    onClicked: {
                        var component = auxiliaryWorkspace.sourceComponent;
                        auxiliaryWorkspace.sourceComponent = mainWorkspace.sourceComponent;
                        mainWorkspace.sourceComponent = component;
                    }
                }
            }
        }

        Loader {
            id: mainWorkspace
            Layout.fillWidth: true
            Layout.fillHeight: true
            sourceComponent: mapComponent
        }
    }


    Component {
        id: mapComponent

        MapView {
            id: map
        }
    }

    Component {
        id: videoComponent

        VideoView {
            id: video
        }
    }
}
