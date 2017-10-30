#include "unified_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

class UnifiedPresenter::Impl
{
public:

};

UnifiedPresenter::UnifiedPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{}

UnifiedPresenter::~UnifiedPresenter()
{}

void UnifiedPresenter::connectView(QObject* view)
{
}
