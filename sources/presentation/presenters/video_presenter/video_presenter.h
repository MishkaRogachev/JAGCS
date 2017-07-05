#ifndef VIDEO_PRESENTER_H
#define VIDEO_PRESENTER_H

#include "base_presenter.h"
#include "db_traits.h"

namespace presentation
{
    class VideoProvider;

    class VideoPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit VideoPresenter(QObject* parent = nullptr);
        ~VideoPresenter() override;

        db::VideoSourcePtr video() const;

    public slots:
        void updateSource();

        void setVideo(const db::VideoSourcePtr& video);

    protected:
        void connectView(QObject* view) override;
        void disconnectView(QObject* view) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // VIDEO_PRESENTER_H
