#ifndef LINK_LIST_VM_H
#define LINK_LIST_VM_H

// Internal
#include "dto_traits.h"

class QAbstractItemModel;

namespace presentation
{
    class LinkListVm: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(QAbstractItemModel* links READ links CONSTANT)

    public:
        explicit LinkListVm(QObject* parent = nullptr);
        ~LinkListVm() override;

        QAbstractItemModel* links() const;

    public slots:
        // FIXME: common add method
        void addSerialLink();
        void addUdpLink();
        void addTcpLink();
        void addBluetoothLink();

        void removeLink(const dto::LinkDescriptionPtr& description);

        void filter(const QString& filterString);

    private:
         class Impl;
         QScopedPointer<Impl> const d;
    };
}

#endif // LINK_LIST_VM_H
