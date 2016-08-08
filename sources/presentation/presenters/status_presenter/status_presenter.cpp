#include "status_presenter.h"

// Qt
#include <QGuiApplication>

using namespace presentation;

StatusPresenter::StatusPresenter(QObject* view):
    BasePresenter(view)
{}

void StatusPresenter::quit()
{
    qApp->exit();
}
