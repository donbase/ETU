#include "application.h"
#include <iostream>
int main(int argc, char *argv[])
{
    TApplication a(argc, argv);

    std::cout<<"END";
    return a.exec();
}
