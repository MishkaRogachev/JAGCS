import QtQuick 2.6
import QtQuick.Layouts 1.3

import "../../Controls" as Controls

ColumnLayout {
    id: menu
    
    property string contextText
    property url homeContext: "qrc:/Views/Drawer/TopMenu.qml"

    readonly property alias currentContext: loader.source
    readonly property bool atHome: currentContext == homeContext
    
    function deepIn(source, text, properties) {
        loader.setSource(source, properties);
        contextModel.append({ "source": source.toString(), "text": text, "properties": properties });
        contextText = text;
        return loader.item;
    }

    function backOut(index) {
        var source = contextModel.get(index).source;
        var properties = contextModel.get(index).properties;
        loader.setSource(source, properties);
        contextText = contextModel.get(index).text;

        if (index + 1 < contextModel.count) {
            contextModel.remove(index + 1, contextModel.count - index - 1);
        }
    }
    
    function goTo(source, text, properties) {
        if (!atHome) goHome();
        deepIn(source, text, properties);
    }
    
    function goHome() {
        loader.setSource(homeContext);
        contextText = "";
        contextModel.clear();
        if (!menu.visible) drawer.open();
    }

    function goPlanning() {
        goTo("qrc:/Views/Drawer/Planning/PlanningView.qml", qsTr("Planning"), {})
    }

    function goVehicles() {
        goTo("qrc:/Views/Drawer/Vehicles/VehicleListView.qml", qsTr("Vehicles"), {})
    }

    function goLinks() {
        goTo("qrc:/Views/Drawer/Links/LinkListView.qml", qsTr("Links"), {})
    }

    function goLogbook() {
        goTo("qrc:/Views/Drawer/Links/LinkListView.qml", qsTr("Logbook"), {})
    }

    function goSettings() {
        goTo("qrc:/Views/Drawer/Settings/SettingsMenu.qml", qsTr("Logbook"), {})
    }

    function goAbout() {
        goTo("qrc:/Views/Drawer/About/AboutView.qml", qsTr("Logbook"), {})
    }

    function goQuit() {
        goTo("qrc:/Views/Drawer/Quit/QuitView.qml", qsTr("Logbook"), {})
    }
    
    spacing: sizings.spacing
    onVisibleChanged: {
        if (visible)
        {
            if (currentContext == "") goHome();
        }
        else
        {
            loader.source = "";
            contextText = "";
            contextModel.clear();
        }
    }

    ListModel { id: contextModel }

    RowLayout {
        Layout.maximumWidth: parent.width
        spacing: 0

        Controls.Button {
            tipText: qsTr("Close menu")
            iconSource: "qrc:/icons/left.svg"
            flat: true
            onClicked: drawer.close()
        }

        Controls.Button {
            tipText: qsTr("Home")
            iconSource: "qrc:/icons/home.svg"
            flat: true
            enabled: !atHome
            onClicked: goHome()
        }

        Repeater {
            model: contextModel

            Controls.Button {
                text: model.text + ", "
                flat: true
                visible: index + 1 < contextModel.count
                onClicked: backOut(index)
            }
        }

        Controls.Label {
            text: contextText
            font.bold: true
            Layout.fillWidth: true
        }
    }

    Flickable {
        id: flickable
        contentHeight: loader.height
        flickableDirection: Flickable.AutoFlickIfNeeded
        clip: true
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.margins: sizings.margins

        Controls.ScrollBar.vertical: Controls.ScrollBar {}

        // TODO: heal loader to use qml components instead raw sources
        Loader {
            id: loader
            width: parent.width
            onItemChanged: {
                if (!item || typeof(item) === "undefined") return;

                menu.width = Math.max(sizings.controlBaseSize * 7,
                                      item.implicitWidth + sizings.margins * 2)
                item.height = Qt.binding(function() {
                    return item ? Math.max(item.implicitHeight, flickable.height) : 0;
                });
            }

            Connections {
                target: loader.item
                ignoreUnknownSignals: true
                onImplicitWidthChanged: menu.width = implicitWidth + sizings.margins * 2
            }
        }
    }
}
