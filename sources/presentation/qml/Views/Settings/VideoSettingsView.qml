import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Frame {
    id: root

    property QtObject presenter: factory.createVideoSettingsPresenter(root)


    GridLayout {
        columns: 2
        anchors.fill: parent

        Label {
            text: qsTr("Video source")
        }

        ComboBox {
            id: typeItem
            model: presenter.sources
        }
    }
}
