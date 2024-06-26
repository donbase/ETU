#include "ratio.h"
#include <iostream>

Tratio::Tratio()
{
    numer;
    denom;
}


Tratio::Tratio(const int& x)
{
    numer = x;
    denom = 1;
}


Tratio::Tratio(int a, int b)
{
    numer = a;
    denom = b;
}

void Tratio::evklid(Tratio& r){
    int a = r.numer;
    int b = r.denom;

    if( a == 0)
    {
        r.denom = 1;
    }
    else
    {
        if (a < 0)  a *= -1;
        if (b < 0)  b *= -1;


        while( (a != 0) && (b != 0)){
            if (a > b)
                a %= b;
            else
                b %= a;
        }


        int nod = a+b;
        r.denom /= nod;
        r.numer /= nod;

        if (((r.denom < 0) && (r.numer < 0)) || ((r.denom < 0) && (r.numer > 0)) ) {
            r.denom *= -1;
            r.numer *= -1;
        }
    }

}

ostream& operator<<(ostream& os, Tratio r)
{
    os<<"("<<r.numer<<"/"<<r.denom<<')';
    return os;
}

istream& operator>>(istream& is, Tratio& r)
{

    is>>r.numer>>r.denom;
    r.evklid(r);
    return is;
}

Tratio Tratio::operator* (Tratio r)
{
    Tratio t;
    t.numer = numer * r.numer;
    t.denom = denom * r.denom;

    t.evklid(t);

    return t;

}

Tratio Tratio::operator* (int r)
{
    Tratio t;
    t.numer = numer * r;
    t.denom = denom;
    t.evklid(t);

    return t;

}

Tratio Tratio::operator/ (Tratio r)
{
    Tratio t;
    t.numer = numer * r.denom;
    t.denom = denom * r.numer;

    t.evklid(t);

    return t;

}



Tratio Tratio::operator+ (Tratio r)
{
    Tratio t;
    int denom_1 = denom;
    int denom_2 = r.denom;

    t.denom = denom * r.denom;
    t.numer = t.denom/denom_1 * numer + t.denom/denom_2 * r.numer;

    /*int a = r.numer;
    int b = r.denom;

    while( (a != 0) && (b != 0)){
        if (a > b)
            a %= b;
        else
            b %= a;
    }
    int nod = a+b;
    t.denom /= nod;
    t.numer /= nod;
    */

    t.evklid(t);
    return t;

}

Tratio Tratio::operator- (Tratio r)
{
    Tratio t;
    int denom_1 = denom;
    int denom_2 = r.denom;

    t.denom = denom * r.denom;
    t.numer = t.denom/denom_1 * numer - t.denom/denom_2 * r.numer;

    /*int a = r.numer;
    int b = r.denom;

    while( (a != 0) && (b != 0)){
        if (a > b)
            a %= b;
        else
            b %= a;
    }
    int nod = a+b;
    t.denom /= nod;
    t.numer /= nod;
    */

    t.evklid(t);
    return t;

}

Tratio Tratio::operator- ()
{
    Tratio t;
    t.numer = -numer;
    t.denom = denom;
    return t;

}



bool Tratio::operator!= (int c)
{

    return (numer != c) ;
}

bool Tratio::operator== (Tratio c)
{

    return ((numer == c.numer) && (denom == c.denom));
}




QString& operator<<(QString& s, Tratio r){
    if(r.denom == 1){
        s += QString().setNum(r.numer);
        return s;
    }
    else{
    s+='(';
    s+= QString().setNum(r.numer);
    s += "/";
    s+=QString().setNum(r.denom);
    s+=')';
    }
    return s;
}

