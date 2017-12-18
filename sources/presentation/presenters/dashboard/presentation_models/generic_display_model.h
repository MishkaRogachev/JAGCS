#ifndef GENERIC_DISPLAY_MODEL_H
#define GENERIC_DISPLAY_MODEL_H

// Internal
#include "abstract_display_model.h"

namespace presentation
{
    class GenericDisplayModel: public AbstractDisplayModel
    {
        Q_OBJECT

    public:
        GenericDisplayModel(QObject* parent = nullptr);
        ~GenericDisplayModel() override;

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // GENERIC_DISPLAY_MODEL_H
