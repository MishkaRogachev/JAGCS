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

        QList<AbstractLink*> links() const;

    public slots:
        void sendData(const QByteArray& data);

        virtual void addLink(AbstractLink* link);
        virtual void removeLink(AbstractLink* link);

    signals:
        void linksChanged(QList<AbstractLink*> links);

    protected slots:
        virtual void onDataReceived(const QByteArray& data) = 0;

    protected:
        VehicleService* const m_vehicleService;
        QList<AbstractLink*> m_links;
    };
}

#endif // ABSTRACT_COMMUNICATOR_H
