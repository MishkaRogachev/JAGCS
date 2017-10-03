import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtCharts 2.0
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Frame {
    id: root

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

    signal save()
    signal restore()
    signal remove()
    signal setConnected(bool connected)

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

    RowLayout {
        anchors.fill: parent
        spacing: palette.spacing

        GridLayout {
            columns: 4
            rowSpacing: palette.spacing
            columnSpacing: palette.spacing

            Controls.Label {
                text: qsTr("Type:")
                Layout.columnSpan: 2
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
                text: qsTr("Protocol:")
                Layout.columnSpan: 2
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

            Controls.Button {
                iconSource: chart.visible ? "qrc:/icons/hide.svg" : "qrc:/icons/show.svg"
                onClicked: chart.visible = !chart.visible
                Layout.alignment: Qt.AlignRight
            }

            Controls.Label {
                text: qsTr("Name:")
                Layout.columnSpan: 2
                Layout.fillWidth: true
            }

            Controls.TextField {
                id: nameField
                placeholderText: qsTr("Enter name")
                onEditingFinished: changed = true
                Layout.columnSpan: 2
                Layout.fillWidth: true
            }

            Controls.Label {
                text: qsTr("Port:")
                visible: type == LinkDescription.Udp
                Layout.columnSpan: 2
                Layout.fillWidth: true
            }

            Controls.SpinBox {
                id: portBox
                from: 0
                to: 65535
                visible: type == LinkDescription.Udp
                onValueChanged: changed = true
                Layout.columnSpan: 2
                Layout.fillWidth: true
            }

            Controls.Label {
                text: qsTr("Device:")
                visible: type == LinkDescription.Serial
                Layout.columnSpan: 2
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
                Layout.columnSpan: 2
                Layout.fillWidth: true
            }

            Controls.Label {
                text: qsTr("Baud rate:")
                visible: type == LinkDescription.Serial
                Layout.columnSpan: 2
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
                Layout.columnSpan: 2
                Layout.fillWidth: true
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
                onClicked: save()
                enabled: changed
                Layout.fillWidth: true
            }

            Controls.Button {
                enabled: !changed
                text: connected ? qsTr("Disconnect") : qsTr("Connect")
                iconSource: connected ? "qrc:/icons/disconnect.svg" :
                                        "qrc:/icons/connect.svg"
                onClicked: setConnected(!connected)
                Layout.fillWidth: true
            }

            Controls.DelayButton {
                text: qsTr("Remove")
                iconSource: "qrc:/icons/remove.svg"
                onActivated: remove()
                iconColor: palette.dangerColor
                Layout.fillWidth: true
            }
        }

        ChartView {
            id: chart
            implicitWidth: root.width / 2
            Layout.fillWidth: true
            Layout.fillHeight: true
            antialiasing: true
            animationOptions: ChartView.SeriesAnimations
            backgroundColor: "transparent"
            legend.labelColor: palette.textColor
            legend.alignment: Qt.AlignBottom
            margins.top: 0
            margins.bottom: 0
            visible: false

            ValueAxis {
                id: timeAxis
                labelsColor: palette.textColor
                visible: false
            }

            ValueAxis {
                id: valueAxis
                labelsColor: palette.textColor
            }

            AreaSeries {
                name: qsTr("Bytes sent")
                axisX: timeAxis
                axisY: valueAxis
                borderWidth: 3
                color: palette.positiveColor
                opacity: 0.33
                borderColor: palette.positiveColor

                upperSeries: LineSeries { id: sentSeries }
            }

            AreaSeries {
                name: qsTr("Bytes received")
                axisX: timeAxis
                axisY: valueAxis
                borderWidth: 3
                color: palette.skyColor
                opacity: 0.33
                borderColor: palette.skyColor

                upperSeries: LineSeries { id: recvSeries }
            }
        }
    }
}
