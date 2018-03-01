import QtQuick 2.6

QtObject {
    id: mapFactory

    function create(type) {
        switch (type) {
        case 0: return Qt.createComponent("LocationMapViews/OsmMapView.qml");
        case 1:
            if (with_mapboxgl) return Qt.createComponent("LocationMapViews/MapBoxGlMapView.qml");
            else return Qt.createComponent("LocationMapViews/MapBoxMapView.qml");
        case 2: return Qt.createComponent("LocationMapViews/EsriMapView.qml");
        default: return null;
        }
    }
}
