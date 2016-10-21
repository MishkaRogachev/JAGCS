// Qt
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

// Internal
#include "domain_entry.h"

#include "main_presenter.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("JAGCS");

    QQmlApplicationEngine engine;

    domain::DomainEntry entry;
    presentation::MainPresenter presenter(&entry);

    engine.load(QUrl(QStringLiteral("qrc:/Views/MainView.qml")));
    presenter.setView(engine.rootObjects().first());

    return app.exec();
}
