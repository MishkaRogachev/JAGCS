#ifndef BASE_PRESENTER_H
#define BASE_PRESENTER_H

#include <QObject>

namespace presentation
{
    class BasePresenter : public QObject
    {
        Q_OBJECT

    public:
        explicit BasePresenter(QObject* view);
        BasePresenter(QObject* view, QObject* parent);

    protected:
        QVariant viewProperty(const char* name) const;

    protected slots:
        void setViewProperty(const char* name, const QVariant& value);
        void invokeViewMethod(const char* name, const QVariant& value);

    private:
        QObject* const m_view;
        Q_DISABLE_COPY(BasePresenter)
    };
}

#endif // BASE_PRESENTER_H
