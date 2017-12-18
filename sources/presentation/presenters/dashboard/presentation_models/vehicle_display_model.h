#ifndef VEHICLE_DISPLAY_MODEL_H
#define VEHICLE_DISPLAY_MODEL_H

// Qt
#include <QAbstractListModel>

// Internal
#include "dao_traits.h"

namespace presentation
{
    class VehicleDisplayModel: public QAbstractListModel
    {
        Q_OBJECT

    public:
        enum VehicleMapItemRoles
        {
            InstrumentRole = Qt::UserRole + 1,
            VehicleIdRole
        };

        VehicleDisplayModel(const dao::VehiclePtr& vehicle, QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

    protected:
        QHash<int, QByteArray> roleNames() const override;

    protected:
        dao::VehiclePtr m_vehicle;
    };
}

#endif // VEHICLE_DISPLAY_MODEL_H
