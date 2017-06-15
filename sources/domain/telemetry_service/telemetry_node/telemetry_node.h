#ifndef TELEMETRY_NODE_H
#define TELEMETRY_NODE_H

//Internal
#include <QObject>

#include "telemetry_traits.h"

namespace domain
{
    class TelemetryNode: public QObject
    {
        Q_OBJECT

    public:
        TelemetryNode(TelemetryId id, TelemetryNode* parentNode = nullptr);
        ~TelemetryNode() override;

        TelemetryId id() const;

        QVariant parameter(TelemetryId id) const;
        TelemetryMap parameters() const;

        TelemetryList changedParameterKeys() const;
        TelemetryMap takeChangedParameters();

        TelemetryNode* parentNode() const;
        TelemetryNode* childNode(TelemetryId id);
        TelemetryNode* childNode(const TelemetryList& path);
        QList<TelemetryNode*> childNodes() const;

    public slots:
        void setParameter(TelemetryId id, const QVariant& value);
        void setParameter(const TelemetryList& path, const QVariant& value);
        void notify();

    signals:
        void parametersChanged(TelemetryMap parameters);

    protected:
        void addChildNode(TelemetryNode* childNode);
        void removeChildNode(TelemetryNode* childNode);

    private:
        const TelemetryId m_id;
        TelemetryMap m_parameters;
        TelemetryList m_changedParameters;

        TelemetryNode* const m_parentNode;
        QMap<TelemetryId, TelemetryNode*> m_childNodes;
    };
}

#endif // TELEMETRY_NODE_H
