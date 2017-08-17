#ifndef BASE_INSTRUMENT_PRESENTER_H
#define BASE_INSTRUMENT_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace presentation
{
    class BaseInstrumentPresenter: public QObject
    {
        Q_OBJECT

    public:
        BaseInstrumentPresenter(QObject* parent = nullptr);

    public slots:
        void addInstrumentView(QObject* view);

        void setViewsProperty(const char* name, const QVariant& value);

    protected:
        virtual void connectView(QObject* view);

        QList<QObject*> m_views;
    };
}

#endif // BASE_INSTRUMENT_PRESENTER_H
