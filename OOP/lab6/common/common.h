#ifndef COMMON_H
#define COMMON_H

#include <QString>

enum messages
{
    SET_SIZE_REQUEST = 1,
    RANK_ANSWER,
    PRINT_DET_REQUEST,
    PRINT_RANK_REQUEST,
    PRINT_TRANS_REQUEST,
    DET_ANSWER,
    TRANS_ANSWER,
};


enum modes {
    REAL_MODE = 1,
    COMPLEX_MODE,
    RATIO_MODE,
};

//extern const QString separator;
QString& operator<< (QString&,const QString&);
#endif // COMMON_H
