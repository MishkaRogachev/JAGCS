#ifndef ABSTRACT_COMMUNICATOR_H
#define ABSTRACT_COMMUNICATOR_H

#include <QObject>

namespace domain
{
    class AbstractLink;
    class VehicleService;

    class AbstractCommunicator: public QObject
    {
        Q_OBJECT

    public:
        AbstractCommunicator(VehicleService* vehicleService, QObject* parent);

        virtual QList<AbstractLink*> links() const = 0;

    public slots:
        virtual void addLink(AbstractLink* link) = 0;
        virtual void removeLink(AbstractLink* link) = 0;

    signals:
        void linksChanged(QList<AbstractLink*> links);

    protected:
        VehicleService* const m_vehicleService;
    };
}

#endif // ABSTRACT_COMMUNICATOR_H
