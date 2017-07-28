#ifndef TRANSLATION_MANAGER_H
#define TRANSLATION_MANAGER_H

// Qt
#include <QString>
#include <QScopedPointer>

namespace domain
{
    class TranslationManager
    {
    public:
        TranslationManager();
        ~TranslationManager();

        QStringList avalibleLocales();
        QString currentLocale();

        void setCurrentLocale(const QString& locale);

        void loadLocales();
        void updateLocale();

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // TRANSLATION_MANAGER_H
