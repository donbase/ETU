#ifndef COMPLEX_H
#define COMPLEX_H
#include <QString>
#include <iostream>
using namespace std;

class Tcomplex
{
    double re, im;
public:
    Tcomplex();
    Tcomplex(const int&);
    Tcomplex(int, int);

    Tcomplex operator* (Tcomplex);
    Tcomplex operator+ (Tcomplex);
    Tcomplex operator- (Tcomplex);
    Tcomplex operator- ();
    Tcomplex operator/ (Tcomplex);
    bool operator!= (int);
    bool operator== (Tcomplex);
    friend ostream& operator<<(ostream&, Tcomplex);
    friend istream& operator>>(istream&, Tcomplex&);
    friend QString& operator<<(QString&, Tcomplex);
};



#endif // COMPLEX_H
