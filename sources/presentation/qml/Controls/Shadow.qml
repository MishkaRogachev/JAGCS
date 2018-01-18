import QtQuick 2.6
import QtGraphicalEffects 1.0

RectangularGlow {
    id: shadow

    property Item source

    glowRadius: sizings.shadowSize
    spread: 0.2
    color: "#77000000"
    cornerRadius: (source.radius ? source.radius : 0) + glowRadius
    anchors.centerIn: source
    anchors.verticalCenterOffset: 1
    anchors.horizontalCenterOffset: 1
    width: source.width
    height: source.height
    z: -1
}
