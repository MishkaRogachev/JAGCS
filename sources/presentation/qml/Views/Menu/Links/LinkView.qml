import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtCharts 2.0
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Frame {
    id: linkView

    property int linkId: 0
    property bool connected: false
    property int type: LinkDescription.UnknownType
    property alias name: nameField.text
    property alias port: portBox.value
    property int protocol: LinkDescription.UnknownProtocol
    property string device
    property alias devices: deviceBox.model
    property int baudRate
    property alias baudRates: baudBox.model
    property bool changed: false
    property var bytesSent: []
    property var bytesRecv: []

    onBytesSentChanged: {
        sentSeries.clear();

        if (timeAxis.max < bytesSent.length - 1) timeAxis.max = bytesSent.length - 1;

        for (var i = 0; i < bytesSent.length; ++i) {
            if (bytesSent[i] > valueAxis.max) valueAxis.max = bytesSent[i];
            sentSeries.append(i, bytesSent[i]);
        }
    }

    onBytesRecvChanged: {
        recvSeries.clear();

        if (timeAxis.max < bytesRecv.length - 1) timeAxis.max = bytesRecv.length - 1;

        for (var i = 0; i < bytesRecv.length; ++i) {
            if (bytesRecv[i] > valueAxis.max) valueAxis.max = bytesRecv[i];
            recvSeries.append(i, bytesRecv[i]);
        }
    }

    onDeviceChanged: deviceBox.currentIndex = deviceBox.model.indexOf(device)
    onBaudRateChanged: baudBox.currentIndex = baudBox.model.indexOf(baudRate)
    contentHeight: grid.height

    LinkPresenter {
        id: presenter
        view: linkView

        Component.onCompleted: {
            updateRates();
            setLink(linkId);
        }
    }

    GridLayout {
        id: grid
        anchors.centerIn: parent
        width: parent.width
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

        Controls.Label {
            text: qsTr("Device")
            visible: type == LinkDescription.Serial
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            id: deviceBox
            visible: type == LinkDescription.Serial
            model: []
            onCurrentTextChanged: {
                device = currentText;
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
            onCurrentTextChanged: {
                baudRate = currentText;
                changed = true;
            }
            Layout.fillWidth: true
        }

        ChartView {
            id: chart
            implicitHeight: width / 3
            Layout.fillWidth: true
            Layout.columnSpan: 2
            antialiasing: true
            backgroundColor: "transparent"
            legend.labelColor: palette.textColor
            legend.alignment: Qt.AlignLeft
            margins.top: 0
            margins.bottom: 0
            visible: false

            ValueAxis {
                id: timeAxis
                visible: false
            }

            ValueAxis {
                id: valueAxis
                visible: false
            }

            AreaSeries {
                name: qsTr("Sent")
                axisX: timeAxis
                axisY: valueAxis
                borderWidth: 3
                color: palette.positiveColor
                opacity: 0.33
                borderColor: palette.positiveColor

                upperSeries: LineSeries { id: sentSeries }
            }

            AreaSeries {
                name: qsTr("Recv.")
                axisX: timeAxis
                axisY: valueAxis
                borderWidth: 3
                color: palette.skyColor
                opacity: 0.33
                borderColor: palette.skyColor

                upperSeries: LineSeries { id: recvSeries }
            }
        }

        Controls.Label {
            text: qsTr("Actions")
            Layout.fillWidth: true
        }

        RowLayout {
            enabled: linkId > 0

            Controls.Button {
                iconSource: chart.visible ? "qrc:/icons/hide.svg" : "qrc:/icons/show.svg"
                onClicked: chart.visible = !chart.visible
            }

            Controls.Button {
                enabled: !changed
                tipText: connected ? qsTr("Disconnect") : qsTr("Connect")
                iconSource: connected ? "qrc:/icons/disconnect.svg" :
                                        "qrc:/icons/connect.svg"
                onClicked: presenter.setConnected(!connected)
            }

            Controls.Button {
                tipText: qsTr("Save")
                iconSource: "qrc:/icons/save.svg"
                onClicked: presenter.save()
                enabled: changed
            }

            Controls.Button {
                tipText: qsTr("Restore")
                iconSource: "qrc:/icons/restore.svg"
                onClicked: presenter.updateLink()
                enabled: changed
            }

            Controls.DelayButton {
                tipText: qsTr("Remove")
                iconSource: "qrc:/icons/remove.svg"
                iconColor: palette.dangerColor
                onActivated: presenter.remove()
            }
        }
    }
}
