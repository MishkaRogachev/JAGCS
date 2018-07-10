#include "plugins_presenter.h"

// Qt

#include <QDebug>

// Internal

using namespace presentation;

class PluginsPresenter::Impl
{
public:
   
};

PluginsPresenter::PluginsPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{}

PluginsPresenter::~PluginsPresenter()
{}
