#ifndef VIDEO_SERVICE_H
#define VIDEO_SERVICE_H

// Qt
#include <QObject>

// Internal
#include "dao_traits.h"

namespace domain
{
    class VideoService: public QObject
    {
        Q_OBJECT

    public:
        explicit VideoService(QObject* parent = nullptr);
        ~VideoService() override;

        dao::VideoSourcePtr videoSource(int id) const;
        dao::VideoSourcePtrList videoSources() const;

    public slots:
        bool save(const dao::VideoSourcePtr& videoSource);
        bool remove(const dao::VideoSourcePtr& videoSource);

    signals:
        void videoSourceAdded(dao::VideoSourcePtr videoSource);
        void videoSourceRemoved(dao::VideoSourcePtr videoSource);
        void videoSourceChanged(dao::VideoSourcePtr videoSource);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // VIDEO_SERVICE_H
