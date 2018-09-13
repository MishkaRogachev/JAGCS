import QtQuick 2.6

Item {
    id: root

    property alias vmProperty: forwardBinding.property
    property alias control: reverseBinding.target
    property alias property: reverseBinding.property

    Binding {
        id: forwardBinding
        target: viewModel
        value: control[property]
        when: control.activeFocus
    }

    Binding {
        id: reverseBinding
        value: viewModel[vmProperty]
        when: !control.activeFocus
    }
}
