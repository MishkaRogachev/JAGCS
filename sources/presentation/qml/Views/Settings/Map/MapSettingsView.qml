import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls
import "../../Map"

ColumnLayout {
    id: root

    property bool changed: false

    property alias plugin: pluginBox.currentIndex
    property alias cacheSize: cacheSizeBox.value
    property alias osmActiveMapType: osmActiveMapTypeBox.currentIndex
    property alias mapBoxGlActiveMapType: mapBoxGlActiveMapTypeBox.currentIndex
    property alias highdpiTiles: highdpiTilesBox.checked
    property alias trackLength: trackLengthSlider.value

    signal save()
    signal restore()

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
                    model: [ "OSM", "Map Box" ]
                    onCurrentIndexChanged: changed = true
                    Layout.fillWidth: true
                }

                Controls.Label {
                    text: qsTr("Map type")
                    Layout.fillWidth: true
                }

                Controls.ComboBox {
                    id: osmActiveMapTypeBox
                    model: []
                    onCurrentIndexChanged: changed = true
                    Layout.fillWidth: true
                    visible: plugin === 0
                }

                Controls.ComboBox {
                    id: mapBoxGlActiveMapTypeBox
                    model: []
                    onCurrentIndexChanged: changed = true
                    Layout.fillWidth: true
                    visible: plugin === 1
                }

                // TODO: customize OSM tile host
                //        Controls.Label {
                //            text: qsTr("Tile host")
                //            Layout.fillWidth: true
                //        }

                //        Controls.TextField {
                //            id: tileHostField
                //            placeholderText: qsTr("Enter tile host url")
                //            Layout.fillWidth: true
                //            onTextChanged: changed = true
                //            enabled: mapTypeBox.currentIndex === mapTypeBox.model.length - 1
                //        }

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
                        text: trackLengthSlider.visualValue > -1 ? trackLengthSlider.visualValue.toFixed(0)
                                                                 : qsTr("Infinite")
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

                    switch(mapPlugin) {
                    case 0:
                        osmActiveMapTypeBox.model = types;
                        break;
                    case 1:
                        mapBoxGlActiveMapTypeBox.model = types;
                        break;
                    }
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

