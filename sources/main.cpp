// Qt
#include <QApplication>
#include <QQuickView>
#include <QQmlEngine>
#include <QQmlContext>

// Internal

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QQuickView view;
    view.setSource(QUrl(QStringLiteral("qrc:/Views/MainView.qml")));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    QObject::connect(view.engine(), &QQmlEngine::quit,
                         qApp, &QApplication::quit);
    view.show();
    return app.exec();
}
