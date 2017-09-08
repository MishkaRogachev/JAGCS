#include "palette_manager.h"

// Qt
#include <QQmlContext>
#include <QVariant>

// Internal
#include "presentation_context.h"

using namespace presentation;

PaletteManager::PaletteManager(QObject* parent): QObject(parent)
{}

void PaletteManager::setPalette(const Palette& palette)
{
    PresentationContext::rootContext()->setContextProperty("palette", QVariant::fromValue(palette));
}
