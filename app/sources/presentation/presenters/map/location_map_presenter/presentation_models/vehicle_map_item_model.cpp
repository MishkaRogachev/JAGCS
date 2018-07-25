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
    connect(vehicleService, &domain::VehicleService::vehicleChanged,
            this, &VehicleMapItemModel::onVehicleChanged);

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

    data_source::Telemetry* node = d->telemetryService->vehicleNode(vehicleId);
    dto::VehiclePtr vehicle = d->vehicleService->vehicle(vehicleId);
    if (!node || vehicle.isNull()) return QVariant();

    QVariant data;

    switch (role)
    {
    case VehicleIdRole:
        data = vehicleId;
        break;
    case VehicleNameRole:
        data = vehicle->name();
        break;
    case VehicleTypeRole:
        data = vehicle->type();
        break;
    case VehicleOnlineRole:
        data = vehicle->isOnline();
        break;
    case CoordinateRole:
        data = node->childNode(data_source::Telemetry::Position)->parameter(
                   data_source::Telemetry::Coordinate);
        if (!data.isValid()) data = QVariant::fromValue(QGeoCoordinate());
        break;
    case HomeCoordinateRole:
        data = node->childNode(data_source::Telemetry::HomePosition)->parameter(
                   data_source::Telemetry::Coordinate);
        if (!data.isValid()) data = QVariant::fromValue(QGeoCoordinate());
        break;
    case TargetCoordinateRole:
        data = node->childNode(data_source::Telemetry::Navigator)->parameter(
                   data_source::Telemetry::Coordinate);
        if (!data.isValid()) data = QVariant::fromValue(QGeoCoordinate());
        break;
    case HeadingRole:
        data = node->childNode(data_source::Telemetry::Ahrs)->
                     childNode(data_source::Telemetry::Compass)->parameter(
                   data_source::Telemetry::Heading);
        if (!data.isValid()) data = 0;
        break;
    case CourseRole:
        data = node->childNode(data_source::Telemetry::Satellite)->parameter(
                   data_source::Telemetry::Course);
        if (!data.isValid()) data = 0;
        break;
    case GroundspeedRole:
        data = node->childNode(data_source::Telemetry::Satellite)->parameter(
                   data_source::Telemetry::Groundspeed);
        if (!data.isValid()) data = 0;
        break;
    case SnsFixRole:
        data = node->childNode(data_source::Telemetry::Satellite)->parameter(
                   data_source::Telemetry::Fix);
        if (!data.isValid()) data = -1;
        break;
    case HdopRadiusRole:
        data = node->childNode(data_source::Telemetry::Satellite)->parameter(
                   data_source::Telemetry::Eph);
        if (!data.isValid()) data = 0;
        break;
    case TrackRole:
        data = d->tracks[vehicleId];
        break;
    }

    return data;
}

void VehicleMapItemModel::onVehicleAdded(const dto::VehiclePtr& vehicle)
{
    int vehicleId = vehicle->id();
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    d->vehicleIds.append(vehicleId);

    data_source::Telemetry* node = d->telemetryService->vehicleNode(vehicle->id());
    if (!node) return;

    connect(node->childNode(data_source::Telemetry::Position),
            &data_source::Telemetry::parametersChanged,
            this, [this, vehicleId](const data_source::Telemetry::TelemetryMap& parameters) {
        this->onPositionParametersChanged(vehicleId, parameters);
    });

    connect(node->childNode(data_source::Telemetry::HomePosition),
            &data_source::Telemetry::parametersChanged,
            this, [this, vehicleId](const data_source::Telemetry::TelemetryMap& parameters) {
        this->onHomeParametersChanged(vehicleId, parameters);
    });

    connect(node->childNode(data_source::Telemetry::Navigator),
            &data_source::Telemetry::parametersChanged,
            this, [this, vehicleId](const data_source::Telemetry::TelemetryMap& parameters) {
        this->onTargetParametersChanged(vehicleId, parameters);
    });

    connect(node->childNode(data_source::Telemetry::Ahrs),
            &data_source::Telemetry::parametersChanged,
            this, [this, vehicleId](const data_source::Telemetry::TelemetryMap& parameters) {
        this->onAhrsParametersChanged(vehicleId, parameters);
    });

    connect(node->childNode(data_source::Telemetry::Satellite),
            &data_source::Telemetry::parametersChanged,
            this, [this, vehicleId](const data_source::Telemetry::TelemetryMap& parameters) {
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

void VehicleMapItemModel::onVehicleChanged(const dto::VehiclePtr& vehicle)
{
    QModelIndex index = this->vehicleIndex(vehicle->id());
    if (!index.isValid()) return;

    emit dataChanged(index, index, { VehicleNameRole, VehicleTypeRole, VehicleOnlineRole });
}

QHash<int, QByteArray> VehicleMapItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[VehicleIdRole] = "vehicleId";
    roles[VehicleNameRole] = "vehicleName";
    roles[VehicleTypeRole] = "vehicleType";
    roles[VehicleOnlineRole] = "vehicleOnline";
    roles[CoordinateRole] = "position";
    roles[HomeCoordinateRole] = "homePosition";
    roles[TargetCoordinateRole] = "targetPosition";
    roles[HeadingRole] = "heading";
    roles[CourseRole] = "course";
    roles[GroundspeedRole] = "groundspeed";
    roles[SnsFixRole] = "snsFix";
    roles[HdopRadiusRole] = "hdopRadius";
    roles[TrackRole] = "track";

    return roles;
}

QModelIndex VehicleMapItemModel::vehicleIndex(int vehicleId) const
{
    return this->index(d->vehicleIds.indexOf(vehicleId));
}

void VehicleMapItemModel::onPositionParametersChanged(
        int vehicleId, const data_source::Telemetry::TelemetryMap& parameters)
{
    QModelIndex index = this->vehicleIndex(vehicleId);
    if (!index.isValid()) return;

    if (parameters.contains(data_source::Telemetry::Coordinate))
    {
        auto coordinate = parameters[data_source::Telemetry::Coordinate].value<QGeoCoordinate>();
        if (!coordinate.isValid()) return;

        d->tracks[vehicleId].append(QVariant::fromValue(coordinate));

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
        int vehicleId, const data_source::Telemetry::TelemetryMap& parameters)
{
    Q_UNUSED(parameters)

    QModelIndex index = this->vehicleIndex(vehicleId);
    if (!index.isValid()) return;

    emit dataChanged(index, index, { HomeCoordinateRole });
}

void VehicleMapItemModel::onTargetParametersChanged(
        int vehicleId, const data_source::Telemetry::TelemetryMap& parameters)
{
    Q_UNUSED(parameters)

    QModelIndex index = this->vehicleIndex(vehicleId);
    if (!index.isValid()) return;

    emit dataChanged(index, index, { TargetCoordinateRole });
}


void VehicleMapItemModel::onAhrsParametersChanged(
        int vehicleId, const data_source::Telemetry::TelemetryMap& parameters)
{
    Q_UNUSED(parameters)

    QModelIndex index = this->vehicleIndex(vehicleId);
    if (!index.isValid()) return;

    emit dataChanged(index, index, { HeadingRole });
}

void VehicleMapItemModel::onSatelliteParametersChanged(
        int vehicleId, const data_source::Telemetry::TelemetryMap& parameters)
{
    Q_UNUSED(parameters)

    QModelIndex index = this->vehicleIndex(vehicleId);
    if (!index.isValid()) return;

    emit dataChanged(index, index, { CourseRole, GroundspeedRole, SnsFixRole, HdopRadiusRole });
}
