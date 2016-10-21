#ifndef VIDEO_PRESENTER_H
#define VIDEO_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class VideoPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit VideoPresenter(QObject* parent);
        ~VideoPresenter() override;

    public slots:
        void updateSource();

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // VIDEO_PRESENTER_H
