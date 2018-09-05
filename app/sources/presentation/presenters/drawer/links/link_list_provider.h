#ifndef LINK_LIST_PROVIDER_H
#define LINK_LIST_PROVIDER_H

// Internal
#include "dto_traits.h"

class QAbstractItemModel;

namespace presentation
{
    class LinkListProvider: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(QAbstractItemModel* links READ links CONSTANT)

    public:
        explicit LinkListProvider(QObject* parent = nullptr);
        ~LinkListProvider() override;

        QAbstractItemModel* links() const;

    public slots:
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

#endif // LINK_LIST_PROVIDER_H
