#ifndef PRESENTATION_CONTEXT_H
#define PRESENTATION_CONTEXT_H

// Internal
#include <QObject>

class QQmlContext;
class QQmlApplicationEngine;

namespace presentation
{
    class PresentationContext
    {

    public:
        PresentationContext();
        virtual ~PresentationContext();

        static PresentationContext* instance();

        QObject* rootView();
        QQmlContext* rootContext();

        void start();

        void updateGeometry();
        void updateGeometry(bool fullscreen);
        void saveWindowedGeometry();

    private:
        QQmlApplicationEngine* m_engine;

        static PresentationContext* lastCreatedContext;

        Q_DISABLE_COPY(PresentationContext)
    };
}

#define presentationContext (presentation::PresentationContext::instance())

#endif // PRESENTATION_CONTEXT_H
