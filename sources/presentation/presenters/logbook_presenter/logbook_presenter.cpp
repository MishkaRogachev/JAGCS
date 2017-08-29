#include "logbook_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "service_registry.h"

using namespace presentation;

class LogbookPresenter::Impl
{
public:

};

LogbookPresenter::LogbookPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{}

LogbookPresenter::~LogbookPresenter()
{}

void LogbookPresenter::connectView(QObject* view)
{}
