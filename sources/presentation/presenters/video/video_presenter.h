#ifndef VIDEO_PRESENTER_H
#define VIDEO_PRESENTER_H

#include "base_presenter.h"
#include "dao_traits.h"

namespace presentation
{
    class VideoProvider;

    class VideoPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit VideoPresenter(QObject* parent = nullptr);
        ~VideoPresenter() override;

        dao::VideoSourcePtr video() const;

    public slots:
        void updateSource();

        void setVideo(const dao::VideoSourcePtr& video);

    protected:
        void connectView(QObject* view) override;
        void disconnectView(QObject* view) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // VIDEO_PRESENTER_H
