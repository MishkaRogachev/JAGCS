#ifndef ABSTRACT_DISPLAY_MODEL_H
#define ABSTRACT_DISPLAY_MODEL_H

// Qt
#include <QAbstractListModel>

namespace presentation
{
    class AbstractDisplayModel: public QAbstractListModel
    {
        Q_OBJECT

    public:
        enum VehicleMapItemRoles
        {
            InstrumentRole = Qt::UserRole + 1,
            VehicleIdRole
        };

        AbstractDisplayModel(QObject* parent = nullptr);

    protected:
        QHash<int, QByteArray> roleNames() const override;
    };
}

#endif // ABSTRACT_DISPLAY_MODEL_H
