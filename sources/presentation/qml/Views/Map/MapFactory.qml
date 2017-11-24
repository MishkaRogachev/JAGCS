import QtQuick 2.6

QtObject {
    id: mapFactory

    function create(type) {
        switch (type) {
        case 0: return Qt.createComponent("LocationMapViews/OsmMapView.qml");
        case 1: return Qt.createComponent("LocationMapViews/MapBoxGlMapView.qml");
        case 2: return Qt.createComponent("LocationMapViews/EsriMapView.qml");
        default: return null;
        }
    }
}
