#ifndef VIDEO_SERVICE_H
#define VIDEO_SERVICE_H

// Qt
#include <QObject>

// Internal
#include "dto_traits.h"

namespace domain
{
    class VideoService: public QObject
    {
        Q_OBJECT

    public:
        explicit VideoService(QObject* parent = nullptr);
        ~VideoService() override;

        dto::VideoSourcePtr videoSource(int id) const;
        dto::VideoSourcePtrList videoSources() const;

    public slots:
        bool save(const dto::VideoSourcePtr& videoSource);
        bool remove(const dto::VideoSourcePtr& videoSource);

    signals:
        void videoSourceAdded(dto::VideoSourcePtr videoSource);
        void videoSourceRemoved(dto::VideoSourcePtr videoSource);
        void videoSourceChanged(dto::VideoSourcePtr videoSource);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // VIDEO_SERVICE_H
