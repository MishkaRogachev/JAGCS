#include "translation_manager.h"

// Qt
#include <QMap>
#include <QDir>
#include <QCoreApplication>
#include <QTranslator>

// Internal
#include "settings.h"
#include "settings_provider.h"

using namespace domain;

class TranslationManager::Impl
{
public:
    QMap<QString, QTranslator*> localeTranslators;
    QString locale;
};

TranslationManager::TranslationManager():
    d(new Impl())
{
    this->loadLocales();
}

TranslationManager::~TranslationManager()
{}

QStringList TranslationManager::avalibleLocales()
{
    return d->localeTranslators.keys();
}

QString TranslationManager::currentLocale()
{
    return d->locale;
}

void TranslationManager::setCurrentLocale(const QString& locale)
{
    if (d->locale == locale) return;

    if (!d->locale.isEmpty())
    {
        qApp->removeTranslator(d->localeTranslators.value(d->locale, nullptr));
    }

    if (!locale.isEmpty())
    {
        qApp->installTranslator(d->localeTranslators.value(locale, nullptr));
    }

    settings::Provider::setValue(settings::gui::locale, locale);
    d->locale = locale;
}

void TranslationManager::loadLocales()
{
    while (!d->localeTranslators.isEmpty())
    {
        delete d->localeTranslators.take(d->localeTranslators.firstKey());
    }

    QDir dir(":/");
    for (const QString& fileName: dir.entryList(QStringList("jagcs_*.qm")))
    {
        QString locale = fileName;
        locale.remove(0, locale.indexOf('_') + 1);
        locale.chop(3);

        d->localeTranslators[locale] = new QTranslator(qApp);
        d->localeTranslators[locale]->load(fileName, ":/");
    }
}

void TranslationManager::updateLocale()
{
    d->locale = settings::Provider::value(settings::gui::locale).toString();
    qApp->installTranslator(d->localeTranslators.value(d->locale, nullptr));
}
