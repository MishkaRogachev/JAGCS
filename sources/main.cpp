// Qt
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

// Internal
#include "domain_entry.h"
#include "settings.h"
#include "settings_provider.h"
#include "translation_manager.h"

#include "main_presenter.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("JAGCS");
    app.setOrganizationName("JAGCS");

    domain::TranslationManager::init();

    domain::DomainEntry entry;
    presentation::MainPresenter presenter(&entry);

    QQmlApplicationEngine engine(QUrl("qrc:/Views/MainView.qml"));
    presenter.setView(engine.rootObjects().first());

    presenter.setMode("mission");

    return app.exec();
}
