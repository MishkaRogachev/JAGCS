#include "radio_status_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "service_registry.h"

#include "telemetry_service.h"
#include "telemetry.h"

using namespace presentation;

class RadioStatusPresenter::Impl
{
public:
    domain::Telemetry* node = serviceRegistry->telemetryService()->radioNode();
};

RadioStatusPresenter::RadioStatusPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    connect(d->node, &domain::Telemetry::parametersChanged,
            this, &RadioStatusPresenter::updateParameters);
}

RadioStatusPresenter::~RadioStatusPresenter()
{}

void RadioStatusPresenter::updateParameters()
{
    this->setViewProperty(PROPERTY(rssi), d->node->parameter(domain::Telemetry::Rssi));
    this->setViewProperty(PROPERTY(remoteRssi), d->node->parameter(domain::Telemetry::RemoteRssi));
}
