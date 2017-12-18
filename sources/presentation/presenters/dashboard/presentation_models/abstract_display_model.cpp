#include "abstract_display_model.h"

// Qt
#include <QDebug>

using namespace presentation;

AbstractDisplayModel::AbstractDisplayModel(QObject* parent):
    QAbstractListModel(parent)
{}

QHash<int, QByteArray> AbstractDisplayModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[InstrumentRole] = "instrument";
    roles[VehicleIdRole] = "vehicleId";

    return roles;
}
