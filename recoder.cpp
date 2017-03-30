#include "recoder.h"

void recoder::attach(std::ostream *o)
{
    out=o;
    num=0;
    buf=0;
}

recoder::recoder(std::ostream *o)
{
    attach(o);
}

void recoder::write(std::string s)
{
    while(1)
    {
        if(num>7)
            num=0;
        if(s.size()==0)
            break;
        if(s.back()=='1')
        {
            buf=buf | (0x01 << num);
        }
        s.pop_back();
        num++;
        if(num==7)
        {
            out->put(buf);
            buf=0;
        }
    }
}

void recoder::end()
{
    out->put(buf);
    num=0;    
}