#ifndef MOCK_LINK_H
#define MOCK_LINK_H

#include "abstract_link.h"

class QSerialPort;

namespace data_source
{
    class MockLink: public AbstractLink
    {
        Q_OBJECT

    public:
        MockLink(QObject* parent = nullptr);

        bool isConnected() const override;
        bool waitData(int timeout = 5000) override;

        QList<MockLink*> links() const;

    public slots:
        void connectLink() override;
        void disconnectLink() override;

        void addLink(MockLink* link);
        void removeLink(MockLink* link);

    signals:
        void linkAdded(MockLink* link);
        void linkRemoved(MockLink* link);

    protected:
        bool sendDataImpl(const QByteArray& data) override;

    private:
        QList<MockLink*> m_links;
    };
}

#endif // MOCK_LINK_H
