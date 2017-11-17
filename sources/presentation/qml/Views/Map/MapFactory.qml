import QtQuick 2.6

QtObject {
    id: mapFactory

    function create() {
        switch (parseInt(settings.value("Map/plugin"))) {
        case 0: return Qt.createComponent("LocationMapViews/OsmMapView.qml");
        case 1: return Qt.createComponent("LocationMapViews/MapBoxGlMapView.qml");
        case 2: return Qt.createComponent("LocationMapViews/EsriMapView.qml");
        default: return null;
        }
    }
}
