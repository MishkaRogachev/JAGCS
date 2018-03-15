import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtCharts 2.0
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators
import "qrc:/Views/Common"

Controls.Frame {
    id: linkEditView

    property int linkId: 0
    property bool connected: false
    property bool changed: false

    property int type: LinkDescription.UnknownType
    property int protocol: LinkDescription.UnknownProtocol
    property string device
    property int baudRate
    property var statistics

    property alias name: nameField.text
    property alias devices: deviceBox.model
    property alias baudRates: baudBox.model
    property alias port: portBox.value
    property alias endpoints: endpointList.endpoints
    property alias autoAddEndpoint: autoAddEndpointBox.checked

    onChangedChanged: if (!changed) endpointList.updateEndpoints(false)
    onDeviceChanged: deviceBox.currentIndex = deviceBox.model.indexOf(device)
    onBaudRateChanged: baudBox.currentIndex = baudBox.model.indexOf(baudRate)

    implicitHeight: grid.implicitHeight
    implicitWidth: sizings.controlBaseSize * 11

    LinkEditPresenter {
        id: presenter
        view: linkEditView

        Component.onCompleted: {
            updateRates();
            setLink(linkId);
        }
    }

    GridLayout {
        id: grid
        anchors.fill: parent
        columns: 2
        rowSpacing: sizings.spacing
        columnSpacing: sizings.spacing

        Controls.Label {
            text: qsTr("Type")
            Layout.fillWidth: true
        }

        Controls.Label {
            text: {
                switch (type) {
                case LinkDescription.Udp: return qsTr("UDP");
                case LinkDescription.Serial: return qsTr("Serial");
                default: return qsTr("Unknown");
                }
            }
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Protocol")
            Layout.fillWidth: true
        }

        Controls.Label {
            text: {
                switch (protocol) {
                case LinkDescription.MavLink1: return "MAVLink v1";
                case LinkDescription.MavLink2: return "MAVLink v2";
                case LinkDescription.UnknownProtocol: return qsTr("Unknown");
                default: return qsTr("Unknown");
                }
            }
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Name")
            Layout.fillWidth: true
        }

        Controls.TextField {
            id: nameField
            placeholderText: qsTr("Enter name")
            onEditingFinished: changed = true
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Device")
            visible: type == LinkDescription.Serial
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            id: deviceBox
            visible: type == LinkDescription.Serial
            model: []
            onDisplayTextChanged: {
                device = displayText;
                changed = true;
            }
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Baud rate")
            visible: type == LinkDescription.Serial
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            id: baudBox
            visible: type == LinkDescription.Serial
            model: []
            onDisplayTextChanged: {
                baudRate = displayText;
                changed = true;
            }
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Port")
            visible: type == LinkDescription.Udp
            Layout.fillWidth: true
        }

        Controls.SpinBox {
            id: portBox
            from: 0
            to: 65535
            visible: type == LinkDescription.Udp
            onValueChanged: changed = true
            Layout.fillWidth: true
        }

        EndpointListView {
            id: endpointList
            visible: type == LinkDescription.Udp
            onChanged: linkEditView.changed = true;
            Layout.maximumHeight: sizings.controlBaseSize * 6
            Layout.fillWidth: true
            Layout.columnSpan: 2
        }

        Controls.CheckBox {
            id: autoAddEndpointBox
            text: qsTr("Auto add endpoints")
            visible: type == LinkDescription.Udp
            horizontalAlignment: Text.AlignHCenter
            onCheckedChanged: changed = true
            Layout.fillWidth: true
            Layout.columnSpan: 2
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.columnSpan: 2

            Indicators.MiniPlot {
                id: plot
                width: parent.width
                height: Math.min(width / 2, parent.height)
                visible: parent.height > 5
                anchors.bottom: parent.bottom

                ValueAxis {
                    id: timeAxis
                    visible: false
                    min: statistics.minTime
                    max: statistics.maxTime
                }

                AreaSeries {
                    color: palette.positiveColor
                    borderColor: palette.positiveColor
                    borderWidth: 3
                    opacity: 0.33
                    axisX: timeAxis
                    axisY: ValueAxis {
                        titleText: qsTr("Recv.")
                        titleFont.pixelSize: sizings.fontPixelSize * 0.5
                        labelsFont.pixelSize: 1
                        labelsVisible: false
                        color: palette.positiveColor
                        max: statistics.maxRecv
                    }
                    upperSeries: LineSeries {
                        VXYModelMapper {
                            xColumn: 0
                            yColumn: 1
                            model: statistics
                        }
                    }
                }

                AreaSeries {
                    color: palette.skyColor
                    borderColor: palette.skyColor
                    borderWidth: 3
                    opacity: 0.33
                    axisX: timeAxis
                    axisYRight: ValueAxis {
                        titleText: qsTr("Sent")
                        titleFont.pixelSize: sizings.fontPixelSize * 0.5
                        labelsVisible: false
                        labelsFont.pixelSize: 1
                        color: palette.skyColor
                        max: statistics.maxSent
                    }
                    upperSeries: LineSeries {
                        VXYModelMapper {
                            xColumn: 0
                            yColumn: 2
                            model: statistics
                        }
                    }
                }
            }
        }

        Controls.Button {
            enabled: !changed
            text: connected ? qsTr("Disconnect") : qsTr("Connect")
            iconSource: connected ? "qrc:/icons/disconnect.svg" : "qrc:/icons/connect.svg"
            onClicked: presenter.setConnected(!connected)
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        SaveRestore {
            enabled: changed
            onSave: presenter.save()
            onRestore: presenter.updateLink()
            Layout.columnSpan: 2
        }
    }
}
