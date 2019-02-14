#include "swarm_map_item_model.h"

// Qt
#include <QMap>
#include <QGeoCoordinate>
#include <QUrl>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "telemetry_service.h"
#include "telemetry.h"

using namespace presentation;

class SwarmMapItemModel::Impl
{
public:
    domain::TelemetryService* telemetryService;
};

SwarmMapItemModel::SwarmMapItemModel(domain::TelemetryService* telemetryService, QObject* parent):
    QAbstractListModel(parent),
    d(new Impl())
{
    d->telemetryService = telemetryService;
    domain::Telemetry* node = d->telemetryService->swarmNode();

    connect(node->childNode(domain::Telemetry::Poi), &domain::Telemetry::parametersChanged,
            this, &SwarmMapItemModel::onSwarmPoiParametersChanged);
}

SwarmMapItemModel::~SwarmMapItemModel()
{}

int SwarmMapItemModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 1;
}

QVariant SwarmMapItemModel::data(const QModelIndex& index, int role) const
{
    Q_UNUSED(index)

    domain::Telemetry* node = d->telemetryService->swarmNode()->childNode(domain::Telemetry::Poi);
    QVariant data;

    switch (role)
    {
    case SwarmPoiCoordinateRole:
        data = node->parameter(domain::Telemetry::Coordinate);
        if (!data.isValid()) data = QVariant::fromValue(QGeoCoordinate());
        break;
    case SwarmPoiGroupRole:
        data = node->parameter(domain::Telemetry::Group);
        if (!data.isValid()) data = 0;
        break;
    case SwarmPoiNumberRole:
        data = node->parameter(domain::Telemetry::Number);
        if (!data.isValid()) data = 0;
        break;
    case SwarmPoiConfirmed:
        data = node->parameter(domain::Telemetry::Confirmed);
        if (!data.isValid()) data = false;
        break;
    }

    return data;
}

QHash<int, QByteArray> SwarmMapItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[SwarmPoiCoordinateRole] = "swarmPoiPosition";
    roles[SwarmPoiGroupRole] = "swarmPoiGroup";
    roles[SwarmPoiNumberRole] = "swarmPoiNumber";
    roles[SwarmPoiConfirmed] = "swarmPoiConfirmed";

    return roles;
}

void SwarmMapItemModel::onSwarmPoiParametersChanged(const domain::Telemetry::TelemetryMap& parameters)
{
    Q_UNUSED(parameters)

    QModelIndex index = this->index(0);
    emit dataChanged(index, index, { SwarmPoiCoordinateRole, SwarmPoiGroupRole, SwarmPoiNumberRole, SwarmPoiConfirmed });
}
