#ifndef LINK_TRAITS_H
#define LINK_TRAITS_H

// Qt
#include <QHostAddress>

namespace domain
{
    using Endpoint = QPair<QHostAddress, quint16>;
}

#endif // LINK_TRAITS_H
