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

        bool isAddEnabled() const;
        QList<AbstractLink*> links() const;

    public slots:
        void setAddEnabled(bool addEnabled);
        void sendData(const QByteArray& data);

        virtual void addLink(AbstractLink* link);
        virtual void removeLink(AbstractLink* link);

    signals:
        void addEnabledChanged(bool addEnabled);
        void linksChanged(QList<AbstractLink*> links);

    protected slots:
        virtual void onDataReceived(const QByteArray& data) = 0;

    protected:
        VehicleService* const m_vehicleService;
        bool m_addEnabled;
        QList<AbstractLink*> m_links;
    };
}

#endif // ABSTRACT_COMMUNICATOR_H
