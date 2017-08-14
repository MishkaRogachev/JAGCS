#ifndef ABSTRACT_COMMUNICATOR_H
#define ABSTRACT_COMMUNICATOR_H

#include <QObject>

namespace comm
{
    class AbstractLink;

    class AbstractCommunicator: public QObject
    {
        Q_OBJECT

    public:
        enum Protocol
        {
            Unknown,
            MavLink1,
            MavLink2
        };

        AbstractCommunicator(QObject* parent);

        QList<AbstractLink*> links() const;

        virtual bool isAddLinkEnabled() = 0;

    public slots:
        void sendDataAllLinks(const QByteArray& data);

        virtual void addLink(AbstractLink* link);
        virtual void removeLink(AbstractLink* link);

    signals:
        void addLinkEnabledChanged(bool addLinkEnabled);
        void linkAdded(AbstractLink* link);
        void linkRemoved(AbstractLink* link);

        void linkStatisticsChanged(AbstractLink* link, int bytesReceived, int bytesSent);
        // TODO: to MavLinkCommunicator
        void mavLinkStatisticsChanged(AbstractLink* link, int packetsReceived, int packetsDrops);
        void mavLinkProtocolChanged(AbstractLink* link, Protocol protocol);

    protected slots:
        virtual void onDataReceived(const QByteArray& data) = 0;

    protected:
        void timerEvent(QTimerEvent* event) override;

    private:
        QList<AbstractLink*> m_links;
        int m_statisticsTimer = 0;

        Q_ENUM(Protocol)
    };
}

#endif // ABSTRACT_COMMUNICATOR_H
