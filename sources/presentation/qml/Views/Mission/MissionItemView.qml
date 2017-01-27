import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

Frame {
    id: root

    property QtObject item

    property var avalibleCommands
    property string command

    signal remove()
    signal setCommand(string command)

    function pick() {
        if (pickButton.visible) pickButton.pick();
    }

    ColumnLayout {
        width: parent.width

        RowLayout {
            Label {
                font.bold: true
                text: qsTr("#") + item.sequence
            }

            ComboBox {
                model: avalibleCommands
                Layout.fillWidth: true
                currentIndex: avalibleCommands ?
                                  avalibleCommands.indexOf(command) : -1
                onCurrentTextChanged: root.setCommand(currentText)
            }

            MapPickButton {
                id: pickButton
                enabled: 'latitude' in item || 'longitude' in item
                onPicked: {
                    latitudeSpinBox.value = coordinate.latitude;
                    longitudeSpinBox.value = coordinate.longitude;
                }
            }

            Button {
                iconSource: "qrc:/icons/up.svg"
                enabled: !item.isFirst()
                onClicked: item.moveUp()
            }

            Button {
                iconSource: "qrc:/icons/down.svg"
                enabled: !item.isLast()
                onClicked: item.moveDown()
            }

            Button {
                iconSource: "qrc:/icons/remove.svg"
                iconColor: palette.negativeColor
                onClicked: root.remove()
            }
        }

        GridLayout {
            columns: 2

            Label {
                visible: 'latitude' in item
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignRight
                text: qsTr("Lat.:")
            }

            CoordSpinBox {
                visible: 'latitude' in item
                Layout.fillWidth: true
                id: latitudeSpinBox
                value: visible ? item.latitude : 0
                onValueChanged: if (!isNaN(value) && visible) item.setLatitude(value)
            }

            Label {
                visible: 'longitude' in item
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignRight
                text: qsTr("Lon.:")
            }

            CoordSpinBox {
                visible: 'longitude' in item
                Layout.fillWidth: true
                id: longitudeSpinBox
                isLongitude: true
                value: visible ? item.longitude : 0
                onValueChanged: if (!isNaN(value) && visible) item.setLongitude(value)
            }

            Label {
                visible: 'altitude' in item
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignRight
                text: qsTr("Alt.:")
            }

            RowLayout {
                SpinBox {
                    id: altitudeBox
                    visible: 'altitude' in item
                    Layout.fillWidth: true
                    from: -1000
                    to: 20000
                    value: visible ? item.altitude.toFixed(2) : 0
                    onValueChanged: if (!isNaN(value) && visible) item.setAltitude(value)
                }

                CheckBox {
                    visible: 'relativeAltitude' in item
                    Layout.fillWidth: true
                    text: qsTr("Rel.")
                    checked: 'relativeAltitude' in item ? item.relativeAltitude : false
                    onCheckedChanged: {
                        if (!visible || checked === item.relativeAltitude) return;

                        altitudeBox.value = item.altitude + (checked ?
                                    -item.homeAltitude() : item.homeAltitude());
                        item.setRelativeAltitude(checked)
                    }
                }
            }

            Label {
                visible: 'pitch' in item
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignRight
                text: qsTr("Pitch:")
            }

            SpinBox {
                visible: 'pitch' in item
                Layout.fillWidth: true
                from: 0
                to: 360
                value: visible ? item.pitch.toFixed(2) : 0
                onValueChanged: if (!isNaN(value) && visible) item.setPitch(value)
            }

            Label {
                visible: 'acceptanceRadius' in item
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignRight
                text: qsTr("Radius:")
            }

            SpinBox {
                visible: 'acceptanceRadius' in item
                Layout.fillWidth: true
                from: 0
                to: 5000
                value: visible ? item.acceptanceRadius.toFixed(2) : 0
                onValueChanged: if (!isNaN(value) && visible) item.setAcceptanceRadius(value)
            }

            Label {
                visible: 'radius' in item
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignRight
                text: qsTr("Radius:")
            }

            SpinBox {
                visible: 'radius' in item
                Layout.fillWidth: true
                from: 0
                to: 5000
                value: visible ? item.radius.toFixed(2) : 0
                onValueChanged: if (!isNaN(value) && visible) item.setRadius(value)
            }

            Label {
                visible: 'turns' in item
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignRight
                text: qsTr("Turns:")
            }

            SpinBox {
                visible: 'turns' in item
                Layout.fillWidth: true
                from: 0
                to: 99
                value: visible ? item.turns : 0
                onValueChanged: if (!isNaN(value) && visible) item.setTurns(value)
            }
        }
    }
}
