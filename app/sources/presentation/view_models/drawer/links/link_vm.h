#ifndef LINK_VM_H
#define LINK_VM_H

// Internal
#include "communication_link.h"

namespace domain
{
    class CommunicationService;
}

namespace presentation
{
    class LinkVm: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(data_source::LinkDescriptionPtr description WRITE setDescription)

        Q_PROPERTY(QString name READ name WRITE setName NOTIFY linkChanged)
        Q_PROPERTY(QString protocol READ protocol WRITE setProtocol NOTIFY linkChanged)
        Q_PROPERTY(data_source::LinkDescription::Type type READ type NOTIFY linkChanged)

        Q_PROPERTY(bool connected READ isConnected WRITE setConnected NOTIFY connectedChanged)

        Q_PROPERTY(float bytesRecv READ bytesRecv NOTIFY statisticsChanged)
        Q_PROPERTY(float bytesSent READ bytesSent NOTIFY statisticsChanged)

        Q_PROPERTY(QStringList availableProtocols READ availableProtocols
                   NOTIFY availableProtocolsChanged)

    public:
        explicit LinkVm(QObject* parent = nullptr);

        QString name() const;
        QString protocol() const;
        data_source::LinkDescription::Type type() const;
        bool isConnected() const;
        float bytesRecv() const;
        float bytesSent() const;

        QStringList availableProtocols() const;

    public slots:
        void setDescription(const data_source::LinkDescriptionPtr& description);

        void remove();
        void setConnected(bool isConnected);
        void setName(const QString& name);
        void setProtocol(const QString& protocol);

    signals:
        void recv();
        void sent();

        void linkChanged();
        void connectedChanged();
        void statisticsChanged();

        void availableProtocolsChanged();

    protected:
        data_source::LinkDescriptionPtr m_description;
        domain::CommunicationService* const m_commService;
    };
}

#endif // LINK_VM_H
