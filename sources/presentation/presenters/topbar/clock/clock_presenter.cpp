#include "clock_presenter.h"

// Qt
#include <QDebug>
#include <QTimerEvent>
#include <QDateTime>

namespace
{
    const int interval = 1000;
}

using namespace presentation;

ClockPresenter::ClockPresenter(QObject* parent):
    BasePresenter(parent)
{}

void ClockPresenter::start()
{
    if (m_timerId) this->stop();

    m_timerId = this->startTimer(::interval);
    this->updateDateTime();
}

void ClockPresenter::stop()
{
    this->killTimer(m_timerId);
    m_timerId = 0;
}

void ClockPresenter::updateDateTime()
{
    this->setViewProperty(PROPERTY(currentDateTime), QDateTime::currentDateTime());
}

void ClockPresenter::timerEvent(QTimerEvent* event)
{
    if (m_timerId == event->timerId()) this->updateDateTime();

    QObject::timerEvent(event);
}
