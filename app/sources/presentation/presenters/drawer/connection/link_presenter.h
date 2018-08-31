#ifndef LINK_PRESENTER_H
#define LINK_PRESENTER_H

// Internal
#include "link_description.h"

namespace domain
{
    class CommunicationService;
}

namespace presentation
{
    class LinkPresenter: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(QString name READ name WRITE setName NOTIFY propertiesChanged)
        Q_PROPERTY(QString protocol READ protocol WRITE setProtocol NOTIFY propertiesChanged)
        Q_PROPERTY(dto::LinkDescription::Type type READ type NOTIFY propertiesChanged)

        Q_PROPERTY(bool connected READ isConnected WRITE setConnected NOTIFY connectedChanged)

        Q_PROPERTY(float bytesRecv READ bytesRecv NOTIFY statisticsChanged)
        Q_PROPERTY(float bytesSent READ bytesSent NOTIFY statisticsChanged)

    public:
        LinkPresenter(const dto::LinkDescriptionPtr& description = dto::LinkDescriptionPtr(),
                      QObject* parent = nullptr);
        ~LinkPresenter() override;

        QString name() const;
        QString protocol() const;
        dto::LinkDescription::Type type() const;
        bool isConnected() const;
        float bytesRecv() const;
        float bytesSent() const;

        Q_INVOKABLE QVariant parameter(dto::LinkDescription::Parameter key) const;

    public slots:
        void setDescription(const dto::LinkDescriptionPtr& description);

        void remove();
        void setConnected(bool isConnected);
        void setName(const QString& name);
        void setProtocol(const QString& protocol);

        void setParameter(dto::LinkDescription::Parameter key, const QVariant& parameter);

    signals:
        void recv();
        void sent();

        void propertiesChanged();
        void connectedChanged();
        void statisticsChanged();

    private:
         class Impl;
         QScopedPointer<Impl> const d;
    };
}

#endif // LINK_PRESENTER_H
