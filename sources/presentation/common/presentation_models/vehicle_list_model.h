#ifndef VEHICLE_LIST_MODEL_H
#define VEHICLE_LIST_MODEL_H

// Qt
#include <QAbstractListModel>

// Internal
#include "dto_traits.h"

namespace presentation
{
    class VehicleListModel: public QAbstractListModel
    {
        Q_OBJECT

    public:
        enum VehicleListRoles
        {
            VehicleIdRole = Qt::UserRole + 1,
            VehicleTypeRole,
            VehicleNameRole,
            VehicleOnlineRole
        };

        explicit VehicleListModel(QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

    public slots:
        void setVehicles(const dto::VehiclePtrList& vehicles);
        void addVehicle(const dto::VehiclePtr& vehicle);
        void updateVehicle(const dto::VehiclePtr& vehicle);
        void removeVehicle(const dto::VehiclePtr& vehicle);

    protected:
        QHash<int, QByteArray> roleNames() const override;

    private:
        dto::VehiclePtrList m_vehicles;
    };
}

#endif // VEHICLE_LIST_MODEL_H
