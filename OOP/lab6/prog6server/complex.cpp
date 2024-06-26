#include "complex.h"
#include <iostream>
Tcomplex::Tcomplex()
{
    re;
    im;
}

Tcomplex::Tcomplex(const int& r)
{
    re = r;
    im = 0;
}

Tcomplex::Tcomplex(int a, int b){
    re = a;
    im = b;
}

ostream& operator<<(ostream& os, Tcomplex c)
{
    if(c.im < 0){
        os<<"("<<c.re<<' '<<c.im<<"i)";
    }
    else{
        os<<"("<<c.re<<" +"<<c.im<<"i)";
    }
    return os;
}

istream& operator>>(istream& is, Tcomplex& c)
{
    is>>c.re>>c.im;
    return is;
}

Tcomplex Tcomplex::operator* (Tcomplex c)
{
    Tcomplex t;
    t.re = re*c.re - im*c.im;
    t.im = re*c.im + im*c.re;
    return t;

}

Tcomplex Tcomplex::operator/ (Tcomplex c)
{
    Tcomplex t;
    t.re = (re*c.re + im*c.im)/(c.re*c.re + c.im*c.im);
    t.im = (im*c.re - re*c.im)/(c.re*c.re + c.im*c.im);
    return t;

}



Tcomplex Tcomplex::operator+ (Tcomplex c)
{
    Tcomplex t;
    t.re = re + c.re;
    t.im = im + c.im;
    return t;

}

Tcomplex Tcomplex::operator- (Tcomplex c)
{
    Tcomplex t;
    t.re = re - c.re;
    t.im = im - c.im;
    return t;

}

Tcomplex Tcomplex::operator- ()
{
    Tcomplex t;
    t.re = -re;
    t.im = -im;
    return t;

}



bool Tcomplex::operator!= (int c)
{

    return (re!=c) || (im != c);
}

bool Tcomplex::operator== (Tcomplex c)
{

    return (re==c.re) && (im == c.im);
}


QString& operator<<(QString& s, Tcomplex r){
        s+='(';
        s+= QString().setNum(r.re);
        if(r.im > 0){
        s += " + ";
        s += QString().setNum(r.im);
        }
        else{
        s += " - ";
        s += QString().setNum(r.im*(-1));
        }
        s += "i)";

    return s;
}
