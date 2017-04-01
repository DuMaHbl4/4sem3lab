#include "recoder.h"

void recoder::attach(std::ostream *o)
{
    las=0;
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
        if(num>8)
           num=0;
        if(s.size()==0)
            break;
        if(s.front()=='1')
        {
            buf=buf | (0b10000000 >> num);
        }
        s.erase(0,1);
        num++;
        //std::cout<<"num="<<num<<' ';
        if(num==8)
        {
            //std::cout<<(int)buf;
            out->put(buf);
            las++;
            buf=0;
            num=0;
        }
    }
}

void recoder::end()
{
    out->put(buf);
    num=0;    
}