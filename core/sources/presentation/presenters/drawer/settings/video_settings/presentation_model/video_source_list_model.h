#ifndef VIDEO_SOURCE_LIST_MODEL_H
#define VIDEO_SOURCE_LIST_MODEL_H

// Qt
#include <QAbstractListModel>

// Internal
#include "dto_traits.h"

namespace presentation
{
    class VideoSourceListModel: public QAbstractListModel
    {
        Q_OBJECT

    public:
        enum VideoSourceListRoles
        {
            VideoIdRole = Qt::UserRole + 1,
            VideoNameRole,
        };

        explicit VideoSourceListModel(QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

    public slots:
        void setVideos(const dto::VideoSourcePtrList& videos);
        void addVideo(const dto::VideoSourcePtr& video);
        void updateVideo(const dto::VideoSourcePtr& video);
        void removeVideo(const dto::VideoSourcePtr& video);

    protected:
        QHash<int, QByteArray> roleNames() const override;

    private:
        dto::VideoSourcePtrList m_videos;
    };
}

#endif // VIDEO_SOURCE_LIST_MODEL_H
