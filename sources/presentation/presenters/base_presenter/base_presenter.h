#ifndef BASE_PRESENTER_H
#define BASE_PRESENTER_H

#define PROPERTY(x) # x
#define NAME(x) QString(PROPERTY(x))

#include <QObject>

namespace presentation
{
    class BasePresenter : public QObject
    {
        Q_OBJECT

    public:
        explicit BasePresenter(QObject* parent = nullptr);

        QObject* view() const;

    public slots:
        void setView(QObject* view);

    protected:
        QVariant viewProperty(const char* name) const;

        virtual void connectView(QObject* view);
        virtual void disconnectView(QObject* view);

    protected slots:
        void setViewProperty(const char* name, const QVariant& value);
        void invokeViewMethod(const char* name, const QVariant& value);

    protected:
        QObject* m_view;

    private:
        Q_DISABLE_COPY(BasePresenter)
    };
}

#endif // BASE_PRESENTER_H
