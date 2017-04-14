#include "encoder.h"

encoder::encoder(istream *is)
{
    attach(is);
}

void encoder::attach(istream *is)
{
    stream=is;
    c=0;
    num=8;    
}

int encoder::getBit()
{
    if(num>7)
    {
        c=stream->get();
        if(stream->eof())
        {
            return -1;
        }
        num=0;
    }
    if(c & 0b10000000 >> num)
    {
        num++;
        return 1;
    }
    else
    {
        num++;
        return 0;
    }
}
