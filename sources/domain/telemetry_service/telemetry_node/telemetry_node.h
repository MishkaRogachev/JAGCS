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
        explicit TelemetryNode(const QString& name, TelemetryNode* parentNode = nullptr);
        ~TelemetryNode() override;

        QString name() const;

        QStringList parameters() const;
        QVariantList values() const;

        QVariant value(const QString& parameter) const;
        QVariant value(const QStringList& path) const;

        TelemetryNode* parentNode() const;
        TelemetryNode* childNode(const QString& name);
        TelemetryNode* childNode(const QStringList& path);

    public slots:
        void setValue(const QString& parameter, const QVariant& value);
        void setValue(const QStringList& path, const QVariant& value);

    signals:
        void parameterChanged(const QString& parameter, const QVariant& value);
        void parameterChanged(const QStringList& path, const QVariant& value);

    protected:
        void addChildNode(TelemetryNode* childNode);
        void removeChildNode(TelemetryNode* childNode);

    private slots:
        void onChildParameterChanged(const QStringList& path, const QVariant& value);

    private:
        const QString m_name;
        QVariantMap m_parameters;

        TelemetryNode* const m_parentNode;
        QMap<QString, TelemetryNode*> m_childNodes;
    };
}

#endif // TELEMETRY_NODE_H
