#ifndef LINK_LIST_MODEL_H
#define LINK_LIST_MODEL_H

// Qt
#include <QAbstractListModel>

// Internal
#include "link_traits.h"

namespace presentation
{
    class LinkListModel: public QAbstractListModel
    {
        Q_OBJECT

    public:
        enum LinkListRoles
        {
            LinkRole = Qt::UserRole + 1,
            LinkNameRole,
            LinkTypeRole
        };

        explicit LinkListModel(QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

    public slots:
        void setLinks(const data_source::LinkDescriptionPtrList& links);
        void addLink(const data_source::LinkDescriptionPtr& link);
        void updateLink(const data_source::LinkDescriptionPtr& link);
        void removeLink(const data_source::LinkDescriptionPtr& link);

    protected:
        QHash<int, QByteArray> roleNames() const override;

    private:
        data_source::LinkDescriptionPtrList m_links;
    };
}

#endif // LINK_LIST_MODEL_H
