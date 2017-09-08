#ifndef PRESENTATION_CONTEXT_H
#define PRESENTATION_CONTEXT_H

// Internal
#include "base_presenter.h"

class QQmlContext;
class QQmlApplicationEngine;

namespace presentation
{
    class PresentationContext
    {
        PresentationContext();

    public:
        static PresentationContext* instance();

        static QObject* rootView();
        static QQmlContext* rootContext();

        static void load();

    private:
        QQmlApplicationEngine* m_engine;

        Q_DISABLE_COPY(PresentationContext)
    };
}

#endif // PRESENTATION_CONTEXT_H
