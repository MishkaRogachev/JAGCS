#ifndef VIDEO_SETTINGS_PRESENTER_H
#define VIDEO_SETTINGS_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class VideoSettingsPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit VideoSettingsPresenter(QObject* parent);
        ~VideoSettingsPresenter() override;

    public slots:
        void updateSources();
        void updateCurrentSource();

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onSourceSelected(const QString& source);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // VIDEO_SETTINGS_PRESENTER_H
