#ifndef LINK_PROVIDER_H
#define LINK_PROVIDER_H

// Internal
#include "link_description.h"

namespace domain
{
    class CommunicationService;
}

namespace presentation
{
    class LinkProvider: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(dto::LinkDescriptionPtr description READ description WRITE setDescription
                   NOTIFY descriptionChanged)

        Q_PROPERTY(QString name READ name WRITE setName NOTIFY propertiesChanged)
        Q_PROPERTY(QString protocol READ protocol WRITE setProtocol NOTIFY propertiesChanged)
        Q_PROPERTY(dto::LinkDescription::Type type READ type NOTIFY propertiesChanged)

        Q_PROPERTY(bool connected READ isConnected WRITE setConnected NOTIFY connectedChanged)

        Q_PROPERTY(float bytesRecv READ bytesRecv NOTIFY statisticsChanged)
        Q_PROPERTY(float bytesSent READ bytesSent NOTIFY statisticsChanged)

        Q_PROPERTY(QStringList availableProtocols READ availableProtocols
                   NOTIFY availableProtocolsChanged)

    public:
        explicit LinkProvider(QObject* parent = nullptr);

        dto::LinkDescriptionPtr description() const;

        QString name() const;
        QString protocol() const;
        dto::LinkDescription::Type type() const;
        bool isConnected() const;
        float bytesRecv() const;
        float bytesSent() const;

        QStringList availableProtocols() const;
        Q_INVOKABLE QVariant parameter(dto::LinkDescription::Parameter key) const;

    public slots:
        void setDescription(const dto::LinkDescriptionPtr& description);

        void remove();
        void setConnected(bool isConnected);
        void setName(const QString& name);
        void setProtocol(const QString& protocol);

        void setParameter(dto::LinkDescription::Parameter key, const QVariant& parameter);

    signals:
        void descriptionChanged(dto::LinkDescriptionPtr description);

        void recv();
        void sent();

        void propertiesChanged();
        void connectedChanged();
        void statisticsChanged();

        void availableProtocolsChanged();

    protected:
        dto::LinkDescriptionPtr m_description;
        dto::LinkStatisticsPtr m_statistics;
        domain::CommunicationService* const m_commService;
    };
}

#endif // LINK_PROVIDER_H
