import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

MapItemView {
    delegate: MapQuickItem {
        coordinate: homePosition

        sourceItem: Image {
            source: "qrc:/indicators/home_mark.svg"
        }
    }
}
