#ifndef TELSEARCH_GLOBAL_H
#define TELSEARCH_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TELSEARCH_LIBRARY)
#  define TELSEARCHSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TELSEARCHSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // TELSEARCH_GLOBAL_H