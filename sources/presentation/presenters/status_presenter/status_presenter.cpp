#include "status_presenter.h"

// Qt
#include <QGuiApplication>

using namespace presentation;

StatusPresenter::StatusPresenter(QObject* parent):
    BasePresenter(parent)
{}

void StatusPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(setMode(QString)), this, SIGNAL(setMode(QString)));

    connect(view, SIGNAL(quit()), qApp, SLOT(quit()));
}
