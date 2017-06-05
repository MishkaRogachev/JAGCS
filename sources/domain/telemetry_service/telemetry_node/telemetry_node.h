#ifndef TELEMETRY_NODE_H
#define TELEMETRY_NODE_H

//Internal
#include <QObject>
#include <QVariantMap>

namespace domain
{
    class TelemetryNode: public QObject
    {
        Q_OBJECT

    public:
        TelemetryNode(const QString& name, TelemetryNode* parentNode = nullptr);
        ~TelemetryNode() override;

        QString name() const;

        QVariant parameter(const QString& name) const;
        QVariantMap parameters() const;
        QVariantMap allParameters() const;
        QStringList changedParameters() const;

        QVariantMap takeChangedParameters();

        TelemetryNode* parentNode() const;
        TelemetryNode* childNode(const QString& name);
        TelemetryNode* childNode(const QStringList& path);
        QList<TelemetryNode*> childNodes() const;

    public slots:
        void setParameter(const QString& name, const QVariant& value);
        void setParameter(const QStringList& names, const QVariant& value);
        void notify();

    signals:
        void parametersChanged(const QVariantMap& parameters);

    protected:
        void addChildNode(TelemetryNode* childNode);
        void removeChildNode(TelemetryNode* childNode);

    private:
        const QString m_name;
        QVariantMap m_parameters;
        QStringList m_changedParameters;

        TelemetryNode* const m_parentNode;
        QMap<QString, TelemetryNode*> m_childNodes;
    };
}

#endif // TELEMETRY_NODE_H
