#ifndef PROXY_MANAGER_H
#define PROXY_MANAGER_H

#include <QObject>

class QNetworkProxy;

namespace domain
{
    class ProxyManager: public QObject
    {
        Q_OBJECT

    public:
        explicit ProxyManager(QObject* parent = nullptr);
        ~ProxyManager() override;

        QNetworkProxy proxy() const;

    public slots:
        void setProxy(const QNetworkProxy& proxy);

        void load();
        void save();

    signals:
        void proxyChanged(const QNetworkProxy& proxy);
    };
}

#endif // PROXY_MANAGER_H
