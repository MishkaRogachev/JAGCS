// Qt
#include <QApplication>
#include <QQuickView>
#include <QQmlEngine>
#include <QQmlContext>

// Internal
#include "presenters_factory.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QQuickView view;

    presentation::PresentersFactory factory;
    view.rootContext()->setContextProperty("factory", &factory);

    view.setSource(QUrl(QStringLiteral("qrc:/Views/MainView.qml")));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    QObject::connect(view.engine(), &QQmlEngine::quit,
                         qApp, &QApplication::quit);

    view.showMaximized();
    return app.exec();
}
