import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Rectangle {
    id: topbar

    property string currentContext

    color: palette.raisedColor
    height: sizings.controlBaseSize

    TopbarPresenter {
        id: presenter
        view: topbar
    }

    RowLayout {
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        width: menu.width
        clip: true
        visible: menu.visible

        Controls.Button {
            tipText: qsTr("Home")
            iconSource: "qrc:/icons/home.svg"
            flat: true
            enabled: !menu.atHome
            onClicked: menu.home()
        }

        Repeater {
            model: pathModel

            Controls.Button {
                text: model.text
                flat: true
                visible: index + 1 < pathModel.count
                onClicked: menu.backOut(index)
            }
        }

        Controls.Label {
            text: currentContext
            font.bold: true
        }

        Item {
            Layout.fillWidth: true
        }

        Controls.Button {
            tipText: qsTr("Close menu")
            iconSource: "qrc:/icons/right.svg"
            flat: true
            onClicked: menuDrawer.close()
            Layout.alignment: Qt.AlignRight
        }
    }

    Controls.Button {
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        tipText: qsTr("Menu")
        iconSource: "qrc:/icons/burger.svg"
        flat: true
        visible: !menu.visible
        onClicked: menuDrawer.open()
//        highlighted: menuDrawer.position == 1.0
//        onClicked: menuDrawer.isOpened ? menuDrawer.close() : menuDrawer.open()
    }
}
