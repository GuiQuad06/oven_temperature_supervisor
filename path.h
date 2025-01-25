#ifndef PATH_H
#define PATH_H

#if defined(Q_OS_UNIX)
const QString home_path = qgetenv("HOME");
#endif

#endif // PATH_H
