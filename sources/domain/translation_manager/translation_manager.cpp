#include "translation_manager.h"

// Qt
#include <QMap>
#include <QDir>
#include <QApplication>
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
{}

TranslationManager::~TranslationManager()
{
    delete d;
}

TranslationManager* TranslationManager::instance()
{
    static TranslationManager manager;
    return &manager;
}

QStringList TranslationManager::avalibleLocales()
{
    return instance()->d->localeTranslators.keys();
}

QString TranslationManager::currentLocale()
{
    return instance()->d->locale;
}

void TranslationManager::setCurrentLocale(const QString& locale)
{
    if (instance()->d->locale == locale) return;

    if (!instance()->d->locale.isEmpty())
    {
        qApp->removeTranslator(instance()->d->localeTranslators.value(
                                   instance()->d->locale, nullptr));
    }

    if (!locale.isEmpty())
    {
        qApp->installTranslator(instance()->d->localeTranslators.value(
                                    locale, nullptr));
    }

    SettingsProvider::setValue(settings::gui::locale, locale);
    instance()->d->locale = locale;
}

void TranslationManager::init()
{
    QDir dir(":/");
    for (const QString& fileName: dir.entryList(QStringList("jagcs_*.qm")))
    {
        QString locale = fileName;
        locale.remove(0, locale.indexOf('_') + 1);
        locale.chop(3);

        instance()->d->localeTranslators[locale] = new QTranslator(qApp);
        instance()->d->localeTranslators[locale]->load(fileName, ":/");
    }

    instance()->d->locale = SettingsProvider::value(settings::gui::locale).toString();
    qApp->installTranslator(instance()->d->localeTranslators.value(
                                instance()->d->locale, nullptr));
}
