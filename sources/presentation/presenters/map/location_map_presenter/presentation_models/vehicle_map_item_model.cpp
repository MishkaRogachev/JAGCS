#include "vehicle_map_item_model.h"

// Qt
#include <QMap>
#include <QGeoCoordinate>
#include <QUrl>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "vehicle_service.h"
#include "vehicle.h"

#include "telemetry_service.h"
#include "telemetry.h"

using namespace presentation;

class VehicleMapItemModel::Impl
{
public:
    domain::VehicleService* vehicleService;
    domain::TelemetryService* telemetryService;

    QList<int> vehicleIds;
    QMap<int, QVariantList> tracks;
};

VehicleMapItemModel::VehicleMapItemModel(domain::VehicleService* vehicleService,
                                         domain::TelemetryService* telemetryService,
                                         QObject* parent):
    QAbstractListModel(parent),
    d(new Impl())
{
    d->vehicleService = vehicleService;
    d->telemetryService = telemetryService;

    connect(vehicleService, &domain::VehicleService::vehicleAdded,
            this, &VehicleMapItemModel::onVehicleAdded);
    connect(vehicleService, &domain::VehicleService::vehicleRemoved,
            this, &VehicleMapItemModel::onVehicleRemoved);

    for (const dto::VehiclePtr& vehicle: vehicleService->vehicles())
    {
        this->onVehicleAdded(vehicle);
    }
}

VehicleMapItemModel::~VehicleMapItemModel()
{}

int VehicleMapItemModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return d->vehicleIds.count();
}

QVariant VehicleMapItemModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= d->vehicleIds.count()) return QVariant();

    int vehicleId = d->vehicleIds.at(index.row());

    domain::Telemetry* node = d->telemetryService->vehicleNode(vehicleId);
    dto::VehiclePtr vehicle = d->vehicleService->vehicle(vehicleId);
    if (!node || vehicle.isNull()) return QVariant();

    QVariant data;

    switch (role)
    {
    case CoordinateRole:
        data = node->childNode(domain::Telemetry::Position)->parameter(
                   domain::Telemetry::Coordinate);
        if (!data.isValid()) data = QVariant::fromValue(QGeoCoordinate());
        break;
    case HomeCoordinateRole:
        data = node->childNode(domain::Telemetry::HomePosition)->parameter(
                   domain::Telemetry::Coordinate);
        if (!data.isValid()) data = QVariant::fromValue(QGeoCoordinate());
        break;
    case TargetCoordinateRole:
        data = node->childNode(domain::Telemetry::Navigator)->parameter(
                   domain::Telemetry::Coordinate);
        if (!data.isValid()) data = QVariant::fromValue(QGeoCoordinate());
        break;
    case HeadingRole:
        data = node->childNode(domain::Telemetry::Ahrs)->
                     childNode(domain::Telemetry::Compass)->parameter(
                   domain::Telemetry::Heading);
        if (!data.isValid()) data = 0;
        break;
    case CourseRole:
        data = node->childNode(domain::Telemetry::Satellite)->parameter(
                   domain::Telemetry::Course);
        if (!data.isValid()) data = 0;
        break;
    case GroundspeedRole:
        data = node->childNode(domain::Telemetry::Satellite)->parameter(
                   domain::Telemetry::Groundspeed);
        if (!data.isValid()) data = 0;
        break;
    case SnsFixRole:
        data = node->childNode(domain::Telemetry::Satellite)->parameter(
                   domain::Telemetry::Fix);
        if (!data.isValid()) data = -1;
        break;
    case TypeRole:
        data = vehicle->type();
        break;
    case VehicleIdRole:
        data = vehicleId;
        break;
    case MavIdRole:
        data = vehicle->mavId();
        break;
    case TrackRole:
        data = d->tracks[vehicleId];
        break;
    case HdopRadius:
        data = node->childNode(domain::Telemetry::Satellite)->parameter(
                   domain::Telemetry::Eph);
        if (!data.isValid()) data = 0;
        break;
    }

    return data;
}

void VehicleMapItemModel::onVehicleAdded(const dto::VehiclePtr& vehicle)
{
    int vehicleId = vehicle->id();
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    d->vehicleIds.append(vehicleId);

    domain::Telemetry* node = d->telemetryService->vehicleNode(vehicle->id());
    if (!node) return;

    connect(node->childNode(domain::Telemetry::Position),
            &domain::Telemetry::parametersChanged,
            this, [this, vehicleId](const domain::Telemetry::TelemetryMap& parameters) {
        this->onPositionParametersChanged(vehicleId, parameters);
    });

    connect(node->childNode(domain::Telemetry::HomePosition),
            &domain::Telemetry::parametersChanged,
            this, [this, vehicleId](const domain::Telemetry::TelemetryMap& parameters) {
        this->onHomeParametersChanged(vehicleId, parameters);
    });

    connect(node->childNode(domain::Telemetry::Navigator),
            &domain::Telemetry::parametersChanged,
            this, [this, vehicleId](const domain::Telemetry::TelemetryMap& parameters) {
        this->onTargetParametersChanged(vehicleId, parameters);
    });

    connect(node->childNode(domain::Telemetry::Ahrs),
            &domain::Telemetry::parametersChanged,
            this, [this, vehicleId](const domain::Telemetry::TelemetryMap& parameters) {
        this->onAhrsParametersChanged(vehicleId, parameters);
    });

    connect(node->childNode(domain::Telemetry::Satellite),
            &domain::Telemetry::parametersChanged,
            this, [this, vehicleId](const domain::Telemetry::TelemetryMap& parameters) {
        this->onSatelliteParametersChanged(vehicleId, parameters);
    });

    this->endInsertRows();
}

void VehicleMapItemModel::onVehicleRemoved(const dto::VehiclePtr& vehicle)
{
    int row = d->vehicleIds.indexOf(vehicle->id());
    if (row == -1) return;

    this->beginRemoveRows(QModelIndex(), row, row);
    d->vehicleIds.removeOne(vehicle->id());
    d->tracks.remove(vehicle->id());

    this->endRemoveRows();
}

QHash<int, QByteArray> VehicleMapItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[CoordinateRole] = "position";
    roles[HomeCoordinateRole] = "homePosition";
    roles[TargetCoordinateRole] = "targetPosition";
    roles[CourseRole] = "course";
    roles[HeadingRole] = "heading";
    roles[GroundspeedRole] = "groundspeed";
    roles[SnsFixRole] = "snsFix";
    roles[TypeRole] = "type";
    roles[VehicleIdRole] = "vehicleId";
    roles[MavIdRole] = "mavId";
    roles[TrackRole] = "track";
    roles[HdopRadius] = "hdopRadius";

    return roles;
}

QModelIndex VehicleMapItemModel::vehicleIndex(int vehicleId) const
{
    return this->index(d->vehicleIds.indexOf(vehicleId));
}

void VehicleMapItemModel::onPositionParametersChanged(
        int vehicleId, const domain::Telemetry::TelemetryMap& parameters)
{
    QModelIndex index = this->vehicleIndex(vehicleId);
    if (!index.isValid()) return;

    if (parameters.contains(domain::Telemetry::Coordinate))
    {
        d->tracks[vehicleId].append(parameters[domain::Telemetry::Coordinate]);

        int trackLength = settings::Provider::value(settings::map::trackLength).toInt();
        if (trackLength > -1)
        {
            while (d->tracks[vehicleId].length() > trackLength) {
                d->tracks[vehicleId].removeFirst();
            }
        }
    }

    emit dataChanged(index, index, { CoordinateRole });
}

void VehicleMapItemModel::onHomeParametersChanged(
        int vehicleId, const domain::Telemetry::TelemetryMap& parameters)
{
    Q_UNUSED(parameters)

    QModelIndex index = this->vehicleIndex(vehicleId);
    if (!index.isValid()) return;

    emit dataChanged(index, index, { HomeCoordinateRole });
}

void VehicleMapItemModel::onTargetParametersChanged(
        int vehicleId, const domain::Telemetry::TelemetryMap& parameters)
{
    Q_UNUSED(parameters)

    QModelIndex index = this->vehicleIndex(vehicleId);
    if (!index.isValid()) return;

    emit dataChanged(index, index, { TargetCoordinateRole });
}


void VehicleMapItemModel::onAhrsParametersChanged(
        int vehicleId, const domain::Telemetry::TelemetryMap& parameters)
{
    Q_UNUSED(parameters)

    QModelIndex index = this->vehicleIndex(vehicleId);
    if (!index.isValid()) return;

    emit dataChanged(index, index, { HeadingRole });
}

void VehicleMapItemModel::onSatelliteParametersChanged(
        int vehicleId, const domain::Telemetry::TelemetryMap& parameters)
{
    Q_UNUSED(parameters)

    QModelIndex index = this->vehicleIndex(vehicleId);
    if (!index.isValid()) return;

    emit dataChanged(index, index, { CourseRole, SnsFixRole, GroundspeedRole, HdopRadius });
}
