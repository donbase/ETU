#include "common.h"

//extern const QChar separator(';');

QString& operator<< (QString& m, const QString& s)
{
    m += s;
    //m.append(separator);
    return m;
}



