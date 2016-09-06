import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Frame {
    id: root

    property QtObject presenter: factory.createVideoSettingsPresenter(root)

    ColumnLayout{
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true

            Label {
                Layout.fillWidth: true
                text: qsTr("Video source")
            }

            ComboBox {
                id: typeItem
                Layout.fillWidth: true
                model: presenter.sources
            }
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
