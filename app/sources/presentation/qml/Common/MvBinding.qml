import QtQuick 2.6

QtObject {
    id: root

    property bool when: false
    property var viewModelProperty
    property var viewProperty

    onViewModelPropertyChanged: if (!when) viewProperty = viewModelProperty
    onViewPropertyChanged: if (when) viewModelProperty = viewProperty
}
