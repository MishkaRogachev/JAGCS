#ifndef VEHICLE_DISPLAY_MODEL_H
#define VEHICLE_DISPLAY_MODEL_H

// Internal
#include "abstract_display_model.h"
#include "dao_traits.h"

namespace presentation
{
    class VehicleDisplayModel: public AbstractDisplayModel
    {
        Q_OBJECT

    public:
        VehicleDisplayModel(const dao::VehiclePtr& vehicle, QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

    protected:
        dao::VehiclePtr m_vehicle;
    };
}

#endif // VEHICLE_DISPLAY_MODEL_H
