#include "domain_entry.h"

// Internal
#include "settings_provider.h"
#include "link_manager.h"

using namespace domain;

DomainEntry::DomainEntry():
    settings(new SettingsProvider()),
    manager(new LinkManager())
{}

DomainEntry::~DomainEntry()
{
    delete settings;
    delete manager;
}
