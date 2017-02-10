#ifndef FLIGHT_VIEW_HELPER_H
#define FLIGHT_VIEW_HELPER_H

// Internal
#include "vehicle.h"

// Qt
#include <QMap>

namespace presentation
{
    class FlightViewHelper: public QObject
    {
        Q_OBJECT

    public:
        explicit FlightViewHelper(QObject* parent = nullptr);

        Q_INVOKABLE QStringList avaliableCommands() const;

    public slots:
        void executeCommand(const QString& command, QObject* object);

    private:
        QMap<domain::Command, QString> m_commandNames;
    };
}

#endif // FLIGHT_VIEW_HELPER_H
