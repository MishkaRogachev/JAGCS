#ifndef LINK_LIST_MODEL_H
#define LINK_LIST_MODEL_H

// Qt
#include <QAbstractListModel>

// Internal
#include "dto_traits.h"

namespace presentation
{
    class LinkListModel: public QAbstractListModel
    {
        Q_OBJECT

    public:
        enum LinkListRoles
        {
            LinkIdRole = Qt::UserRole + 1,
            LinkNameRole,
        };

        explicit LinkListModel(QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

    public slots:
        void setLinks(const dto::LinkDescriptionPtrList& links);
        void addLink(const dto::LinkDescriptionPtr& link);
        void updateLink(const dto::LinkDescriptionPtr& link);
        void removeLink(const dto::LinkDescriptionPtr& link);

    protected:
        QHash<int, QByteArray> roleNames() const override;

    private:
        dto::LinkDescriptionPtrList m_links;
    };
}

#endif // LINK_LIST_MODEL_H
