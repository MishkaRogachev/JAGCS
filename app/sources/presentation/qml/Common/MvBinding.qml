import QtQuick 2.6

Item {
    id: root

    property alias vm: forwardBinding.target
    property alias vmProperty: forwardBinding.property
    property alias control: reverseBinding.target
    property alias property: reverseBinding.property

    Binding {
        id: forwardBinding
        value: control[property]
        when: control.activeFocus
    }

    Binding {
        id: reverseBinding
        value: vm[vmProperty]
        when: !control.activeFocus
    }
}
