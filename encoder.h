#ifndef ENCODER_H
#define ENCODER_H

#include <iostream>
using namespace std;

class encoder
{
    istream *stream;
    char c; //теуцщий байт
    int num; //порядок
public:
    encoder(istream *is);
    void attach(istream *is);
    int getBit();
};

#endif