import QtQuick 2.6

Item {
    id: root

    property QtObject viewModel
    property string viewModelProperty
    property Item input
    property string inputProperty

    Binding {
        target: viewModel
        property: viewModelProperty
        value: input[inputProperty]
        when: input.activeFocus
    }

    Binding {
        target: input
        property: inputProperty
        value: viewModel[viewModelProperty]
        when: !input.activeFocus
    }
}
