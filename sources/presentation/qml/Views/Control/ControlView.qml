import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls
import "../Map"
import "../Video"

Controls.Pane {
    id: root

    property bool cornerMap: false
    property bool cornerVisible: false

    property alias vehicles: vehiclesBox.model
    property alias selectedVehicle: vehiclesBox.currentIndex

    property alias videos: video.videoSources

    signal selectVehicle(int index)

    ColumnLayout {
        id: column
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        Layout.margins: palette.margins
        spacing: palette.spacing
        width: height * 0.43

        RowLayout {

            Controls.Label {
                text: qsTr("Vehicle")
                font.pixelSize: palette.fontPixelSize * 0.6
                font.bold: true
            }

            Controls.ComboBox {
                id: vehiclesBox
                onCurrentIndexChanged: selectVehicle(currentIndex)
                Layout.fillWidth: true
            }
        }

        DashboardView {
            objectName: "dashboard"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    Item {
        id: background
        anchors.left: column.right
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: palette.margins
    }

    Item {
        id: corner
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: cornerVisible ? (background.height / 3 + palette.controlBaseSize) : 0
        width: cornerMap ? height : video.ratio * height
    }

    MapView {
        id: map
        objectName: "map"
        anchors.fill: cornerMap ? corner : background
        z: cornerMap
    }

    VideoSplitView {
        id: video
        objectName: "video"
        anchors.fill: cornerMap ? background : corner
    }

    Controls.Button {
        onClicked: cornerMap = !cornerMap
        iconSource: cornerMap ? "qrc:/icons/map-marker.svg" :
                                "qrc:/icons/video.svg"
        anchors.bottom: parent.bottom
        anchors.right: cornerVisible ? corner.left : maxMinButton.left
    }

    Controls.Button {
        id: maxMinButton
        onClicked: cornerVisible = !cornerVisible
        iconSource: cornerVisible ? "qrc:/icons/minimize.svg" : "qrc:/icons/maximize.svg"
        anchors.bottom: parent.bottom
        anchors.right: corner.right
        z: 2
    }
}
