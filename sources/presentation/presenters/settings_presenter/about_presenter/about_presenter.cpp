#include "about_presenter.h"

// Qt
#include <QVersionNumber>
#include <QVariant>

using namespace presentation;

AboutPresenter::AboutPresenter(QObject* parent):
    BasePresenter(parent)
{}

void AboutPresenter::connectView(QObject* view)
{
    Q_UNUSED(view)

    this->setViewProperty(PROPERTY(version), QVariant::fromValue(QString("VERSION")));
    this->setViewProperty(PROPERTY(revision), QVariant::fromValue(QString("REVISION")));
    this->setViewProperty(PROPERTY(qtVersion), QVariant::fromValue(
                              QVersionNumber(QT_VERSION).toString()));
}
