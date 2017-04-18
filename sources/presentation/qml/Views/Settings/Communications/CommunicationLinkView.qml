import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtCharts 2.0
import JAGCS 1.0

import "qrc:/Controls"

Frame {
    id: root

    property bool connected: false
    property int type: LinkDescription.UnknownType
    property alias name: nameField.text
    property alias port: portBox.value
    property string device
    property alias devices: deviceBox.model
    property int baudRate
    property alias baudRates: baudBox.model

    signal setName(string name)
    signal setPort(int port)
    signal setDevice(string device)
    signal setBaudRate(int baudRate)
    signal remove()
    signal setConnected(bool connected)

    property int statisticsCount: 0
    property int counter: 0

    function updateStatistics(sentBytes, recvBytes) {
        if (sentSeries.count > statisticsCount) sentSeries.remove(0);
        if (recvSeries.count > statisticsCount) recvSeries.remove(0);

        sentSeries.append(counter, sentBytes);
        recvSeries.append(counter, recvBytes);

        valueAxis.max = Math.max(valueAxis.max, recvBytes);
        valueAxis.max = Math.max(valueAxis.max, sentBytes);

        counter++;
    }

    onConnectedChanged: if (!connected) updateStatistics(0, 0)
    onDeviceChanged: deviceBox.currentIndex = deviceBox.model.indexOf(device)
    onBaudRateChanged: baudBox.currentIndex = baudBox.model.indexOf(baudRate)

    RowLayout {
        anchors.fill: parent

        GridLayout {
            columns: 2
            rowSpacing: palette.spacing

            Label {
                text: qsTr("Type:")
                enabled: false
            }

            Label {
                text: {
                    switch (type) {
                    case LinkDescription.Udp: return qsTr("UDP");
                    case LinkDescription.Serial: return qsTr("Serial");
                    default: return qsTr("Unknown");
                    }
                }
            }

            Label {
                text: qsTr("Name:")
            }

            TextField {
                id: nameField
                placeholderText: qsTr("Enter name")
                onEditingFinished: setName(text)
            }

            Label {
                text: qsTr("Port:")
                visible: type == LinkDescription.Udp
            }

            SpinBox {
                id: portBox
                from: 0
                to: 65535
                decimals: 0
                visible: type == LinkDescription.Udp
                onValueChanged: setPort(value)
            }

            Label {
                text: qsTr("Device:")
                visible: type == LinkDescription.Serial
            }

            ComboBox {
                id: deviceBox
                visible: type == LinkDescription.Serial
                onCurrentTextChanged: setDevice(currentText)
            }

            Label {
                text: qsTr("Baud rate:")
                visible: type == LinkDescription.Serial
            }

            ComboBox {
                id: baudBox
                visible: type == LinkDescription.Serial
                onCurrentTextChanged: setBaudRate(currentText)
            }

            RowLayout {
                Layout.columnSpan: 2

                Item {
                    height: parent.height
                    Layout.fillWidth: true
                }

                Button {
                    text: qsTr("Remove")
                    iconSource: "qrc:/icons/remove.svg"
                    onClicked: remove()
                }

                Button {
                    text: connected ? qsTr("Disconnect") : qsTr("Connect")
                    iconSource: connected ? "qrc:/icons/disconnect.svg" :
                                            "qrc:/icons/connect.svg"
                    onClicked: setConnected(!connected)
                }
            }
        }

        ChartView {
            id: chart
            Layout.fillWidth: true
            Layout.fillHeight: true
            antialiasing: true
            animationOptions: ChartView.SeriesAnimations
            backgroundColor: "transparent"
            legend.labelColor: palette.textColor
            legend.alignment: Qt.AlignRight
            margins.top: 0
            margins.bottom: 0

            ValueAxis {
                id: timeAxis
                min: Math.max(0, counter - statisticsCount)
                max: counter - 1
                labelsColor: palette.textColor
            }

            ValueAxis {
                id: valueAxis
                min: 0
                max: 0
                labelsColor: palette.textColor
            }

            AreaSeries {
                name: qsTr("Bytes sent")
                axisX: timeAxis
                axisY: valueAxis
                borderWidth: 3
                color: palette.positiveColor
                opacity: 0.5
                borderColor: palette.positiveColor

                upperSeries: LineSeries { id: sentSeries }
            }

            AreaSeries {
                name: qsTr("Bytes received")
                axisX: timeAxis
                axisY: valueAxis
                borderWidth: 3
                color: palette.skyColor
                opacity: 0.5
                borderColor: palette.skyColor

                upperSeries: LineSeries { id: recvSeries }
            }
        }
    }
}
