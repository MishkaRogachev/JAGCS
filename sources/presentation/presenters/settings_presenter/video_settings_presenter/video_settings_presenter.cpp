#include "video_settings_presenter.h"

// Qt
#include <QCameraInfo>
#include <QDebug>

using namespace presentation;

class VideoSettingsPresenter::Impl
{
public:
    QList<QCameraInfo> cameras;
};

VideoSettingsPresenter::VideoSettingsPresenter(QObject* view):
    BasePresenter(view),
    d(new Impl())
{}

VideoSettingsPresenter::~VideoSettingsPresenter()
{
    delete d;
}

void VideoSettingsPresenter::connectView(QObject* view)
{
    Q_UNUSED(view)

    this->updateSources();
}

void VideoSettingsPresenter::updateSources()
{
    d->cameras = QCameraInfo::availableCameras();

    QStringList sourcesList;

    sourcesList.append(tr("none"));

    for (const QCameraInfo& info: d->cameras)
        sourcesList.append(info.deviceName());

    this->setViewProperty(PROPERTY(sourcesModel), sourcesList);
}
