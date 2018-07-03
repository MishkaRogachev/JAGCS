#ifndef TRANSLATION_MANAGER_H
#define TRANSLATION_MANAGER_H

// Qt
#include <QString>
#include <QScopedPointer>

namespace presentation
{
    class TranslationManager
    {
    public:
        TranslationManager();
        ~TranslationManager();

        static TranslationManager* instance();

        QStringList avalibleLocales();
        QString currentLocale();

        void setLocale(const QString& locale);

        void clearLocales();
        void reloadLocales();

    private:
        static TranslationManager* lastCreatedManager;

        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#define translationManager (presentation::TranslationManager::instance())

#endif // TRANSLATION_MANAGER_H
