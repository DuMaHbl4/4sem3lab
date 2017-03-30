#ifndef RECODER_H
#define RECODER_H

#include <ostream>

class recoder
{
    int num; //число бит в буфере
    std::ostream *out;	//поток
    unsigned char buf;	//буфер
public:
    void attach(std::ostream *o);
    recoder(std::ostream *o);
    void write(std::string s);
    void end(); //закрываем файл
};

#endif