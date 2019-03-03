import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtCharts 2.0
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import Industrial.Indicators 1.0 as Indicators
import "qrc:/Views/Common"

ColumnLayout {
    id: linkEditView

    property int linkId: 0
    property bool connected: false
    property bool changed: false

    property int type: LinkDescription.UnknownType
    property int protocol: LinkDescription.UnknownProtocol
    property string device
    property int baudRate
    property bool discoveringBluetooth: false
    property var statistics

    property alias name: nameField.text
    property alias devices: deviceBox.model
    property alias baudRates: baudBox.model
    property alias address: addressField.text
    property alias port: portBox.value
    property alias endpoints: endpointList.endpoints
    property alias autoResponse: autoResponseBox.checked

    onChangedChanged: {
        if (changed) return;

        endpointList.updateEndpoints(false);

        if (linkId > 0)
        {
            if (name.length > 0) drawer.submode = name;
            else drawer.submode = qsTr("Link");
        }
        else drawer.submode = "";
    }
    onDeviceChanged: deviceBox.currentIndex = devices.indexOf(device)
    onDevicesChanged: deviceBox.currentIndex = devices.indexOf(device)
    onBaudRateChanged: baudBox.currentIndex = baudRates.indexOf(baudRate)
    onLinkIdChanged: presenter.setLink(linkId);
    Component.onDestruction: drawer.submode = ""

    spacing: industrial.spacing

    LinkEditPresenter {
        id: presenter
        view: linkEditView
        Component.onCompleted: updateRates()
    }

    RowLayout {
        spacing: 0

        Controls.Label {
            text: {
                var str = qsTr("Type");
                switch (type) {
                case LinkDescription.Serial: return str + ": " + qsTr("Serial");
                case LinkDescription.Udp: return str + ": " + qsTr("UDP");
                case LinkDescription.Tcp: return str + ": " + qsTr("TCP");
                case LinkDescription.Bluetooth: return str + ": " + qsTr("Bluetooth");
                default: return str + ": " + qsTr("Unknown");
                }
            }
            Layout.fillWidth: true
        }

        SaveRestore {
            enabled: changed
            onSave: presenter.save()
            onRestore: presenter.updateLink()
        }

        Controls.Button {
            iconSource: connected ? "qrc:/icons/disconnect.svg" : "qrc:/icons/connect.svg"
            tipText: connected ? qsTr("Disconnect") : qsTr("Connect")
            flat:true
            enabled: !changed
            onClicked: presenter.setConnected(!connected)
        }
    }

    Controls.Label {
        text: {
            var str = qsTr("Protocol");
            switch (protocol) {
            case LinkDescription.MavLink1: return str + ": " + "MAVLink v1";
            case LinkDescription.MavLink2: return str + ": " + "MAVLink v2";
            case LinkDescription.UnknownProtocol:
            default: return str + ": " + qsTr("Unknown");
            }
        }
        Layout.fillWidth: true
    }

    Controls.TextField {
        id: nameField
        labelText: qsTr("Name")
        onEditingFinished: changed = true
        Layout.fillWidth: true
    }

    Controls.ComboBox {
        id: baudBox
        labelText: qsTr("Baud rate")
        visible: type == LinkDescription.Serial
        model: []
        onDisplayTextChanged: {
            baudRate = displayText;
            changed = true;
        }
        Layout.fillWidth: true
    }

    Controls.TextField {
        id: addressField
        labelText: qsTr("Address")
        visible: type == LinkDescription.Tcp || type == LinkDescription.Bluetooth
        onTextChanged: changed = true
        Layout.fillWidth: true
    }

    Controls.ComboBox {
        id: deviceBox
        labelText: qsTr("Device")
        visible: type == LinkDescription.Serial || type == LinkDescription.Bluetooth
        model: []
        onDisplayTextChanged: {
            if (type != LinkDescription.Bluetooth) return;

            address = presenter.bluetoothAddress(displayText);
        }
        onActivated: {
            if (device == displayText) return;

            device = displayText;
            changed = true;
        }
        Layout.fillWidth: true
    }

    RowLayout {
        spacing: industrial.spacing
        visible: type == LinkDescription.Bluetooth

        Controls.Button {
            text: qsTr("Start")
            enabled: !discoveringBluetooth
            onClicked: presenter.startBluetoothDiscovery()
            Layout.fillWidth: true
        }

        Controls.Button {
            text: qsTr("Stop")
            enabled: discoveringBluetooth
            onClicked: presenter.stopBluetoothDiscovery()
            Layout.fillWidth: true
        }
    }

    Controls.SpinBox {
        id: portBox
        labelText: qsTr("Port")
        from: 0
        to: 65535
        visible: type == LinkDescription.Udp || type == LinkDescription.Tcp
        onValueChanged: changed = true
        Layout.fillWidth: true
    }

    Controls.Label {
        text: qsTr("Endpoints")
        visible: type == LinkDescription.Udp
        horizontalAlignment: Text.AlignHCenter
        Layout.fillWidth: true
    }

    EndpointListView {
        id: endpointList
        visible: type == LinkDescription.Udp
        onChanged: linkEditView.changed = true;
        Layout.maximumHeight: industrial.baseSize * 6
        Layout.fillWidth: true
    }

    Controls.CheckBox {
        id: autoResponseBox
        text: qsTr("Autoresponse on get data")
        visible: type == LinkDescription.Udp
        horizontalAlignment: Text.AlignHCenter
        onCheckedChanged: changed = true
        Layout.fillWidth: true
    }

    Item {
        Layout.fillHeight: true
        Layout.fillWidth: true

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
                color: industrial.colors.positive
                borderColor: industrial.colors.positive
                borderWidth: 3
                opacity: 0.33
                axisX: timeAxis
                axisY: ValueAxis {
                    titleText: qsTr("Recv.")
                    titleFont.pixelSize: industrial.fontSize * 0.5
                    labelsFont.pixelSize: 1
                    labelsVisible: false
                    color: industrial.colors.positive
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
                color: Indicators.Theme.skyColor
                borderColor: Indicators.Theme.skyColor
                borderWidth: 3
                opacity: 0.33
                axisX: timeAxis
                axisYRight: ValueAxis {
                    titleText: qsTr("Sent")
                    titleFont.pixelSize: industrial.fontSize * 0.5
                    labelsVisible: false
                    labelsFont.pixelSize: 1
                    color: Indicators.Theme.skyColor
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
}

