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

    property int statisticsCounter: 0
    property int statisticsCount: 0

    function updateStatistics(sentBytes, recvBytes) {
        if (sentSeries.count > statisticsCount)
        {
            sentSeries.remove(0);
            recvSeries.remove(0);
        }
        sentSeries.append(statisticsCounter, sentBytes);
        recvSeries.append(statisticsCounter, recvBytes);
        statisticsCounter++;
    }

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
            backgroundRoundness: 0

            ValueAxis {
                id: timeAxis
                min: Math.max(0, statisticsCounter - statisticsCount)
                max: statisticsCounter
                tickCount: 1
            }

            ValueAxis {
                id: valueAxis
                min: 0
                max: 10
            }

            LineSeries {
                id: sentSeries
                name: qsTr("Bytes sent")
                color: palette.neutralColor
                axisX: timeAxis
                axisY: valueAxis
            }

            LineSeries {
                id: recvSeries
                name: qsTr("Bytes sent")
                color: palette.positiveColor
                axisX: timeAxis
                axisY: valueAxis
            }
        }
    }
}
