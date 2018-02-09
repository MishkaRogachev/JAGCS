#ifndef VEHICLES_MODEL_H
#define VEHICLES_MODEL_H

// Qt
#include <QAbstractListModel>

// Internal
#include "dao_traits.h"

namespace presentation
{
    class VehiclesModel: public QAbstractListModel
    {
        Q_OBJECT

    public:
        enum VehicleMapItemRoles
        {
            VehicleTypeRole = Qt::UserRole + 1,
            VehicleIdRole
        };

        explicit VehiclesModel(QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

    public slots:
        void setVehicles(const dao::VehiclePtrList& vehicles);
        void addVehicle(const dao::VehiclePtr& vehicle);
        void removeVehicle(const dao::VehiclePtr& vehicle);

    protected:
        QHash<int, QByteArray> roleNames() const override;

    private:
        dao::VehiclePtrList m_vehicles;
    };
}

#endif // VEHICLES_MODEL_H
