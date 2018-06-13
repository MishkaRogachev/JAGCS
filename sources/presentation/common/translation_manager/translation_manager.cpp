#include "translation_manager.h"

// Qt
#include <QMap>
#include <QDir>
#include <QCoreApplication>
#include <QTranslator>
#include <QPointer>
#include <QDebug>

using namespace presentation;

TranslationManager* TranslationManager::lastCreatedManager = nullptr;

class TranslationManager::Impl
{
public:
    QMap<QString, QTranslator*> localeTranslators;
    QPointer<QTranslator> activeTranslator;
};

TranslationManager::TranslationManager():
    d(new Impl())
{
    TranslationManager::lastCreatedManager = this;

    this->reloadLocales();
}

TranslationManager::~TranslationManager()
{
    for (QTranslator* translator: d->localeTranslators)
    {
        delete translator;
    }
}

TranslationManager* TranslationManager::instance()
{
    return TranslationManager::lastCreatedManager;
}

QStringList TranslationManager::avalibleLocales()
{
    return d->localeTranslators.keys();
}

QString TranslationManager::currentLocale()
{
    return d->localeTranslators.key(d->activeTranslator);
}

void TranslationManager::setLocale(const QString& locale)
{
    QTranslator* translator = d->localeTranslators.value(locale, nullptr);

    if (d->activeTranslator == translator) return;

    if (d->activeTranslator)
    {
        qApp->removeTranslator(d->activeTranslator);
    }

    d->activeTranslator = translator;
    if (d->activeTranslator)
    {
        qApp->installTranslator(d->activeTranslator);
    }

    // TODO: Qt 5.10 QQmlEngine::retranslate
}

void TranslationManager::clearLocales()
{
    while (!d->localeTranslators.isEmpty())
    {
        delete d->localeTranslators.take(d->localeTranslators.firstKey());
    }
}

void TranslationManager::reloadLocales()
{
    this->clearLocales();

    QDir dir(":/");
    for (const QString& fileName: dir.entryList(QStringList("jagcs_*.qm")))
    {
        QString locale = fileName;
        locale.remove(0, locale.indexOf('_') + 1);
        locale.chop(3);

        d->localeTranslators[locale] = new QTranslator();
        d->localeTranslators[locale]->load(fileName, ":/");
    }
}

