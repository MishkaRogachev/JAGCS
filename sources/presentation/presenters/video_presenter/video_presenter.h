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
        explicit VideoPresenter(const db::VideoSourcePtr& video, QObject* parent);
        ~VideoPresenter() override;

    public slots:
        void updateSource();

    protected:
        void connectView(QObject* view) override;
        void disconnectView(QObject* view) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // VIDEO_PRESENTER_H
