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
        AbstractCommunicator(QObject* parent);

        QList<AbstractLink*> links() const;

        virtual bool isAddLinkEnabled() = 0;

    public slots:
        void sendDataAllLinks(const QByteArray& data);

        virtual void addLink(AbstractLink* link);
        virtual void removeLink(AbstractLink* link);

    signals:
        void addLinkEnabledChanged(bool addLinkEnabled);
        void linksChanged();

    protected slots:
        virtual void onDataReceived(const QByteArray& data) = 0;

    protected:
        QList<AbstractLink*> m_links;
    };
}

#endif // ABSTRACT_COMMUNICATOR_H
