#include "home_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

HomePresenter::HomePresenter(domain::Telemetry* positionNode,
                             domain::Telemetry* homePositionNode,
                             QObject* parent):
    BaseInstrumentPresenter(parent),
    m_positionNode(positionNode),
    m_homePositionNode(homePositionNode)
{
    connect(positionNode, &domain::Telemetry::parametersChanged,
            this, &HomePresenter::onPositionChanged);
    connect(homePositionNode, &domain::Telemetry::parametersChanged,
            this, &HomePresenter::onHomePositionChanged);
}

void HomePresenter::onPositionChanged(const domain::Telemetry::TelemetryMap& parameters)
{
    if (!parameters.contains(domain::Telemetry::Coordinate)) return;

    m_position = parameters.value(domain::Telemetry::Coordinate).value<QGeoCoordinate>();
    this->updateViews();
}

void HomePresenter::onHomePositionChanged(const domain::Telemetry::TelemetryMap& parameters)
{
    if (!parameters.contains(domain::Telemetry::Coordinate)) return;

    m_homePosition = parameters.value(domain::Telemetry::Coordinate).value<QGeoCoordinate>();

    this->updateViews();
}

void HomePresenter::updateViews()
{
    if (m_position.isValid() && m_homePosition.isValid())
    {
        this->setViewsProperty(PROPERTY(homeDistance), m_position.distanceTo(m_homePosition));
        this->setViewsProperty(PROPERTY(homeDirection), m_position.azimuthTo(m_homePosition));
    }
    else
    {
        this->setViewsProperty(PROPERTY(homeDistance), 0);
        this->setViewsProperty(PROPERTY(homeDirection), 0);
    }
}

 void HomePresenter::connectView(QObject* view)
 {
     Q_UNUSED(view)

     this->onPositionChanged(m_positionNode->parameters());
     this->onHomePositionChanged(m_homePositionNode->parameters());
}

