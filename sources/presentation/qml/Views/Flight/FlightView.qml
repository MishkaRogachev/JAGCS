import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "../Map"
import "../Video"

Pane {
    id: root

    // TODO: think about removing presenters and usage bare Model-View architecture
    property QtObject presenter: factory.createFlightPresenter(root)

    RowLayout {
        anchors.fill: parent
        anchors.margins: 5

        ColumnLayout {
            id: toolBar
            Layout.fillHeight: true
            Layout.preferredWidth: settingsProvider.value("Gui/toolbarWidth");

            ComboBox {
                enabled: count > 0
                model: presenter.vehicles
                Layout.preferredWidth: parent.width
                onCurrentIndexChanged: {
                    vehicleView.vehicle = presenter.vehicleObject(currentIndex);
                }
            }

            VehicleView {
                id: vehicleView
                Layout.preferredWidth: parent.width
            }

            Item {
                width: 1
                Layout.fillHeight: true
            }

            Loader {
                id: auxiliaryWorkspace
                Layout.preferredWidth: parent.width
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
