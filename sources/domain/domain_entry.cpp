#include "domain_entry.h"

// Internal
#include "settings_provider.h"
#include "connection_manager.h"

using namespace domain;

DomainEntry::DomainEntry():
    settings(new SettingsProvider()),
    manager(new ConnectionManager())
{}

DomainEntry::~DomainEntry()
{
    delete settings;
    delete manager;
}
