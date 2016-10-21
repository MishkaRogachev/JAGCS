#include "status_presenter.h"

// Qt
#include <QGuiApplication>

using namespace presentation;

StatusPresenter::StatusPresenter(QObject* parent):
    BasePresenter(parent)
{}

void StatusPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(showSettings()), this, SIGNAL(showSettings()));
    connect(view, SIGNAL(hideSettings()), this, SIGNAL(hideSettings()));

    connect(view, SIGNAL(quit()), qApp, SLOT(quit()));
}
