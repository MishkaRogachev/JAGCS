#include "status_presenter.h"

// Qt
#include <QGuiApplication>

using namespace presentation;

StatusPresenter::StatusPresenter(QObject* parent):
    QObject(parent)
{}

void StatusPresenter::quit()
{
    qApp->exit();
}
