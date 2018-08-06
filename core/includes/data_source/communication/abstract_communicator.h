#ifndef ABSTRACT_COMMUNICATOR_H
#define ABSTRACT_COMMUNICATOR_H

#include <QObject>

namespace data_source
{
    class AbstractLink;

    class AbstractCommunicator: public QObject
    {
        Q_OBJECT

    public:
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

        void protocolInfoChanged(AbstractLink* link, const QString& info);

    protected slots:
        virtual void onDataReceived(const QByteArray& data) = 0;

    private:
        QList<AbstractLink*> m_links;
    };
}

#endif // ABSTRACT_COMMUNICATOR_H
