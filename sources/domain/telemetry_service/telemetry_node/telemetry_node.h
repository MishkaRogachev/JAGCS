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

        QVariant parameter(const QString& parameter) const;
        QVariantMap parameters() const;

        TelemetryNode* parentNode() const;
        TelemetryNode* childNode(const QString& name);
        TelemetryNode* childNode(const QStringList& path);

    public slots:
        void setParameters(const QVariantMap& parameters);

    signals:
        void parametersChanged(const QVariantMap& parameters);

    protected:
        void addChildNode(TelemetryNode* childNode);
        void removeChildNode(TelemetryNode* childNode);

    private:
        const QString m_name;
        QVariantMap m_parameters;

        TelemetryNode* const m_parentNode;
        QMap<QString, TelemetryNode*> m_childNodes;
    };
}

#endif // TELEMETRY_NODE_H
