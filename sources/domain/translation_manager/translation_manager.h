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
        ~TranslationManager();
        static TranslationManager* instance();

        static QStringList avalibleLocales();
        static QString currentLocale();

        static void setCurrentLocale(const QString& locale);

        static void init();

    private:
        TranslationManager();

        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // TRANSLATION_MANAGER_H
