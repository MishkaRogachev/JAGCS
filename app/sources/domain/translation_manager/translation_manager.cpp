#include "translation_manager.h"

// Qt
#include <QMultiMap>
#include <QDir>
#include <QCoreApplication>
#include <QTranslator>
#include <QPointer>
#include <QDebug>

using namespace domain;

TranslationManager* TranslationManager::lastCreatedManager = nullptr;

class TranslationManager::Impl
{
public:
    QMultiMap<QString, QTranslator*> localeTranslators;
    QString activeLocale;
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
    return d->localeTranslators.uniqueKeys();
}

QString TranslationManager::currentLocale()
{
    return d->activeLocale;
}

void TranslationManager::setLocale(const QString& locale)
{
    if (d->activeLocale == locale) return;

    for (QTranslator* translator: d->localeTranslators.values(d->activeLocale))
    {
        qApp->removeTranslator(translator);
    }

    d->activeLocale = locale;

    for (QTranslator* translator: d->localeTranslators.values(d->activeLocale))
    {
        qApp->installTranslator(translator);
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
    for (const QString& fileName: dir.entryList(QStringList("*_*.qm")))
    {
        QString locale = fileName;
        locale.remove(0, locale.indexOf('_') + 1);
        locale.chop(3);

        QTranslator* translator = new QTranslator(qApp);
        translator->load(fileName, ":/");

        d->localeTranslators.insertMulti(locale, translator);
    }
}

