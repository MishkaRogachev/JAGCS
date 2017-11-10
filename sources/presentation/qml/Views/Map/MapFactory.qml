import QtQuick 2.6

import "LocationMapViews"

Item { // TODO: to builder QtObject
    id: factory

    function create() {
        switch (parseInt(settings.value("Map/plugin"))) {
        case 0: return osm;
        case 1: return mapBoxGl;
        case 2: return esri;
        default: return null;
        }
    }

    Component { id: osm; OsmMapView {} }
    Component { id: mapBoxGl; MapBoxGlMapView {} }
    Component { id: esri; EsriMapView {} }
}
