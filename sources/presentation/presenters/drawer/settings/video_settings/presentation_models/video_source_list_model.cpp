#include "video_source_list_model.h".h"

// Qt
#include <QDebug>

// Internal
#include "video_source.h"

using namespace presentation;

VideoSourceListModel::VideoSourceListModel(QObject* parent):
    QAbstractListModel(parent)
{}

int VideoSourceListModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    return m_videos.count();
}

QVariant VideoSourceListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_videos.count()) return QVariant();

    dto::VideoSourcePtr video = m_videos.at(index.row());

    switch (role)
    {
    case VideoIdRole: return video->id();
    case VideoNameRole: return video->source(); // TODO: video name
    default: return QVariant();
    }
}

void VideoSourceListModel::setVideos(const dto::VideoSourcePtrList& videos)
{
    this->beginResetModel();

    m_videos = videos;

    this->endResetModel();
}

void VideoSourceListModel::addVideo(const dto::VideoSourcePtr& Video)
{
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    m_videos.append(Video);
    this->endInsertRows();
}

void VideoSourceListModel::updateVideo(const dto::VideoSourcePtr& video)
{
    QModelIndex index = this->index(m_videos.indexOf(video));
    if (!index.isValid()) return;

    emit dataChanged(index, index);
}

void VideoSourceListModel::removeVideo(const dto::VideoSourcePtr& video)
{
    int row = m_videos.indexOf(video);

    this->beginRemoveRows(QModelIndex(), row, row);
    m_videos.removeOne(video);
    this->endRemoveRows();
}

QHash<int, QByteArray> VideoSourceListModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[VideoIdRole] = "VideoId";
    roles[VideoNameRole] = "VideoName";

    return roles;
}
