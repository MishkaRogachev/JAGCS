#ifndef VIDEO_PRESENTER_H
#define VIDEO_PRESENTER_H

#include "base_presenter.h"
#include "dto_traits.h"



namespace presentation
{
    class VideoProvider;

    class VideoPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit VideoPresenter(QObject* parent = nullptr);
        ~VideoPresenter() override;

        dto::VideoSourcePtr video() const;

    public slots:
        void updateSource();

        void setVideo(const dto::VideoSourcePtr& video);

    protected:
        void connectView(QObject* view) override;
        void disconnectView(QObject* view) override;

    private slots:
        void onVideoSourceChanged(const dto::VideoSourcePtr& video);
        void onVideoSourceRemoved(const dto::VideoSourcePtr& video);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // VIDEO_PRESENTER_H
