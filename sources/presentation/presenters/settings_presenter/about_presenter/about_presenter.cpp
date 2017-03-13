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

    this->setViewProperty(PROPERTY(version), QVariant::fromValue(
                              QVersionNumber(VERSION_MAJOR,
                                             VERSION_MINOR,
                                             VERSION_PATCH).toString()));
    this->setViewProperty(PROPERTY(revision), QVariant::fromValue(GIT_REVISION));
    this->setViewProperty(PROPERTY(qtVersion), QVariant::fromValue(
                              QVersionNumber(QT_VERSION_MAJOR,
                                             QT_VERSION_MINOR,
                                             QT_VERSION_PATCH).toString()));
}
