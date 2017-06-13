#include "statusbar_presenter.h"

// Qt
#include <QGuiApplication>

using namespace presentation;

StatusbarPresenter::StatusbarPresenter(QObject* parent):
    BasePresenter(parent)
{}

void StatusbarPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(setMode(QString)), this, SIGNAL(setMode(QString)));

    connect(view, SIGNAL(quit()), qApp, SLOT(quit()));
}
