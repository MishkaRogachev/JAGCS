#include "connection_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "service_registry.h"

using namespace presentation;

class ConnectionPresenter::Impl
{
public:
};

ConnectionPresenter::ConnectionPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{}

ConnectionPresenter::~ConnectionPresenter()
{}

