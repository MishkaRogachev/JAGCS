#ifndef ILINK_H
#define ILINK_H

#include <QtCore/QObject>

namespace data_source
{
    class ILink: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(bool up READ isUp NOTIFY upChanged)

    public:
        explicit ILink(QObject* parent = nullptr);

        virtual bool isUp() const = 0;

    public slots:
        virtual void up() = 0;
        virtual void down() = 0;

    signals:
        void upChanged(bool isUp);
    };
}

#endif // ILINK_H
