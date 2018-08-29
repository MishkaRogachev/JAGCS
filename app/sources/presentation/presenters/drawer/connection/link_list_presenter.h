#ifndef LINK_LIST_PRESENTER_H
#define LINK_LIST_PRESENTER_H

// Internal
#include "dto_traits.h"

class QAbstractItemModel;

namespace presentation
{
    class LinkListPresenter: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(QAbstractItemModel* links READ links CONSTANT)
        Q_PROPERTY(QStringList availableProtocols READ availableProtocols
                   NOTIFY availableProtocolsChanged)
        Q_PROPERTY(QVariantList baudRates READ baudRates CONSTANT)

    public:
        explicit LinkListPresenter(QObject* parent = nullptr);
        ~LinkListPresenter() override;

        QAbstractItemModel* links() const;
        QStringList availableProtocols() const;
        QVariantList baudRates() const;

    public slots:
        void addSerialLink();
        void addUdpLink();
        void addTcpLink();
        void addBluetoothLink();

        void filter(const QString& filterString);

    signals:
        void availableProtocolsChanged();

    private slots:
        void onDescriptionAdded(const dto::LinkDescriptionPtr& description);
        void onDescriptionRemoved(const dto::LinkDescriptionPtr& description);

    private:
         class Impl;
         QScopedPointer<Impl> const d;
    };
}

#endif // LINK_LIST_PRESENTER_H
