#include "video_settings_presenter.h"

// Qt
#include <QCameraInfo>
#include <QDebug>

// Internal
#include "settings_provider.h"
#include "settings.h"

using namespace presentation;

class VideoSettingsPresenter::Impl
{
public:
    QList<QCameraInfo> cameras;
};

VideoSettingsPresenter::VideoSettingsPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{}

VideoSettingsPresenter::~VideoSettingsPresenter()
{
    delete d;
}

void VideoSettingsPresenter::connectView(QObject* view)
{
    this->updateSources();

    connect(view, SIGNAL(sourceSelected(QString)),
            this, SLOT(onSourceSelected(QString)));
}

void VideoSettingsPresenter::onSourceSelected(const QString& source)
{
    domain::SettingsProvider::setValue(settings::video::device, source);
}

void VideoSettingsPresenter::updateSources()
{
    d->cameras = QCameraInfo::availableCameras();

    QStringList sourcesList;

    sourcesList.append(tr("none"));

    for (const QCameraInfo& info: d->cameras)
        sourcesList.append(info.deviceName());

    this->setViewProperty(PROPERTY(sourcesModel), sourcesList);

    this->updateCurrentSource();
}

void VideoSettingsPresenter::updateCurrentSource()
{
    this->invokeViewMethod(PROPERTY(setSource), domain::SettingsProvider::value(
                               settings::video::device));
}
