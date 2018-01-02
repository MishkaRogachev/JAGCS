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
        PresentationContext();

    public:
        static PresentationContext* instance();

        static QObject* rootView();
        static QQmlContext* rootContext();

        static void start();

        static void updateGeometry();
        static void updateGeometry(bool fullscreen);
        static void saveWindowedGeometry();

    private:
        QQmlApplicationEngine* m_engine;

        Q_DISABLE_COPY(PresentationContext)
    };
}

#endif // PRESENTATION_CONTEXT_H
