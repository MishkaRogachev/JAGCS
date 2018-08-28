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

    public:
        explicit LinkListPresenter(QObject* parent = nullptr);
        ~LinkListPresenter() override;

        QAbstractItemModel* links() const;

    public slots:
        void addSerialLink();
        void addUdpLink();
        void addTcpLink();
        void addBluetoothLink();

        void filter(const QString& filterString);

    private slots:
        void onDescriptionAdded(const dto::LinkDescriptionPtr& description);
        void onDescriptionRemoved(const dto::LinkDescriptionPtr& description);

    private:
         class Impl;
         QScopedPointer<Impl> const d;
    };
}

#endif // LINK_LIST_PRESENTER_H
