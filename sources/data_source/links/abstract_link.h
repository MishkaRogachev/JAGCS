#ifndef ABSTRACT_LINK_H
#define ABSTRACT_LINK_H

// Internal
#include "abstract_communicator.h"

namespace data_source
{
    class AbstractLink: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(bool isUp READ isUp NOTIFY upChanged)

    public:
        explicit AbstractLink(QObject* parent = nullptr);

        AbstractCommunicator* communicator() const;

        virtual bool isUp() const = 0;

    public slots:
        void setCommunicator(AbstractCommunicator* communicator);

        virtual void up() = 0;
        virtual void down() = 0;

    signals:
        void upChanged(bool isUp);

    protected slots:
        void onDataReceived(const QByteArray& data);

    private slots:
        virtual void sendData(const QByteArray& data) = 0;

    private:
        AbstractCommunicator* m_communicator;
    };
}

#endif // ABSTRACT_LINK_H
