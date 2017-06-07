#include "artificial_horizon_presenter.h"

using namespace presentation;

ArtificialHorizonPresenter::ArtificialHorizonPresenter(QObject* parent):
    AbstractInstrumentPresenter(parent)
{}

void ArtificialHorizonPresenter::onParametersChanged(const QVariantMap& parameters)
{

}

void ArtificialHorizonPresenter::connectView(QObject* view)
{

}
