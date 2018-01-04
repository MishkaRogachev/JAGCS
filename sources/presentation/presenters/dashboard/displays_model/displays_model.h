#ifndef DISPLAYS_MODEL_H
#define DISPLAYS_MODEL_H

// Qt
#include <QAbstractListModel>

// Internal
#include "dao_traits.h"

namespace presentation
{
    class DisplaysModel: public QAbstractListModel
    {
        Q_OBJECT

    public:
        enum VehicleMapItemRoles
        {
            DisplayRole = Qt::UserRole + 1,
            VehicleIdRole
        };

        DisplaysModel(QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

    public slots:
        void addVehicle(const dao::VehiclePtr& vehicle);
        void removeVehicle(const dao::VehiclePtr& vehicle);
        void setSelectedVehicle(const dao::VehiclePtr& vehicle);

    protected:
        QHash<int, QByteArray> roleNames() const override;

    private:
        dao::VehiclePtrList m_vehicles;
        dao::VehiclePtr m_selectedVehicle;
    };
}

#endif // DISPLAYS_MODEL_H
