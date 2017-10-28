import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls
import "../../Map"

ColumnLayout {
    id: root

    property int osmActiveMapType: -1
    property int mapBoxGlActiveMapType: -1
    property int esriActiveMapType: -1

    property bool changed: false

    property alias plugin: pluginBox.currentIndex
    property alias cacheSize: cacheSizeBox.value
    property alias highdpiTiles: highdpiTilesBox.checked
    property alias trackLength: trackLengthSlider.value

    signal save()
    signal restore()

    onOsmActiveMapTypeChanged: updateSelectedMapType()
    onMapBoxGlActiveMapTypeChanged: updateSelectedMapType()

    function updateSelectedMapType() {
        switch (plugin) {
        case 0:
            activeMapTypeBox.currentIndex = osmActiveMapType;
            break;
        case 1:
            activeMapTypeBox.currentIndex = mapBoxGlActiveMapType;
            break;
        case 2:
            activeMapTypeBox.currentIndex = esriActiveMapType;
            break;
        }
    }

    Flickable {
        Layout.fillWidth: true
        Layout.fillHeight: true
        contentHeight: frame.height
        clip: true

        ScrollBar.vertical: Controls.ScrollBar {}

        Controls.Frame {
            id: frame
            width: root.width

            GridLayout {
                width: parent.width
                rowSpacing: palette.spacing
                columns: 2

                Controls.Label {
                    text: qsTr("Map provider")
                    Layout.fillWidth: true
                }

                Controls.ComboBox {
                    id: pluginBox
                    model: [ "OSM", "Map Box", "Esri" ]
                    currentIndex: -1
                    onCurrentIndexChanged: changed = true
                    Layout.fillWidth: true
                }

                Controls.Label {
                    text: qsTr("Map type")
                    Layout.fillWidth: true
                }

                Controls.ComboBox {
                    id: activeMapTypeBox
                    model: []
                    onModelChanged: updateSelectedMapType()
                    onActivated: {
                        switch (plugin) {
                        case 0:
                            osmActiveMapType = index;
                            break;
                        case 1:
                            mapBoxGlActiveMapType = index;
                            break;
                        case 2:
                            esriActiveMapType = index;
                            break;
                        }
                        changed = true;
                    }
                    Layout.fillWidth: true
                }

                Controls.Label {
                    text: qsTr("Cache size")
                    Layout.fillWidth: true
                }

                Controls.SpinBox {
                    id: cacheSizeBox
                    Layout.fillWidth: true
                    onValueChanged: changed = true;
                    to: 2147483647 // TODO: to helper
                }

                Controls.Label {
                    text: qsTr("High DPI tiles")
                    Layout.fillWidth: true
                }

                Controls.CheckBox {
                    id: highdpiTilesBox
                    onCheckedChanged: changed = true
                }

                Controls.Label {
                    text: qsTr("Track length")
                    Layout.fillWidth: true
                }

                RowLayout {
                    Controls.Slider {
                        id: trackLengthSlider
                        from: -1
                        to: 1000
                        Layout.fillWidth: true
                        onPressedChanged: if (!pressed) changed = true
                    }

                    Controls.Label {
                        Layout.preferredWidth: 86
                        horizontalAlignment: Text.AlignHCenter
                        text: trackLengthSlider.visualValue > -1 ?
                                  trackLengthSlider.visualValue.toFixed(0) : qsTr("Infinite")
                    }
                }
            }
        }
    }

    GridLayout {
        columns: 2

        Component {
            id: mapComponent

            MapView {
                id: map
                Component.onCompleted: {
                    var types = new Array(0);
                    for (var i = 0; i < supportedMapTypes.length; ++i) {
                        types.push(supportedMapTypes[i].name);
                    }
                    activeMapTypeBox.model = types;
                }
            }
        }

        Loader {
            id: mapPreview
            Layout.fillWidth: true
            Layout.preferredHeight: Math.max(palette.controlBaseSize * 4, root.height - frame.height)
            Layout.columnSpan: 2
            Component.onCompleted: reload()

            function reload() {
                sourceComponent = null;
                sourceComponent = mapComponent;
            }
        }

        Controls.Button {
            text: qsTr("Restore")
            iconSource: "qrc:/icons/restore.svg"
            onClicked: restore()
            enabled: changed
            Layout.fillWidth: true
        }

        Controls.Button {
            text: qsTr("Save")
            iconSource: "qrc:/icons/save.svg"
            onClicked: {
                save();
                mapPreview.reload();
            }
            enabled: changed
            Layout.fillWidth: true
        }
    }
}
