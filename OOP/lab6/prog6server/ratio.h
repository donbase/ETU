#ifndef RATIO_H
#define RATIO_H
#include <iostream>
#include <QString>
using namespace std;
class Tratio
{
    int numer, denom;
    static QChar SEPARATOR;

public:
    Tratio();
    Tratio(int, int);
    Tratio(const int&);
    Tratio(const QByteArray&);

    Tratio operator* (Tratio);
    Tratio operator* (int);
    Tratio operator+ (Tratio);
    Tratio operator- (Tratio);
    Tratio operator- ();
    Tratio operator/ (Tratio);
    bool operator!= (int);
    bool operator== (Tratio);
    friend ostream& operator<<(ostream&, Tratio);
    friend istream& operator>>(istream&, Tratio&);
    void evklid(Tratio &);

    friend QString& operator<<(QString&, int);
    friend QString& operator<<(QString&, Tratio);
    friend QByteArray& operator>>(QByteArray&, Tratio&);
    operator QString();

};

#endif // RATIO_H
