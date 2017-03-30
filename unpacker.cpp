#include <stdint.h>
#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include "tree.h"
using namespace std;

int main(int argc, char** argv)
{
    if(argc<2)
    {
        cout<<"Укажите имя файла\n";
        return 0;
    }
    ifstream fi(argv[1], ios::binary);
    char ch;
    ch=fi.get();
    bool tr=false;
    if(ch=='H')
    {
        ch=fi.get();
        if(ch=='U')
        {
            ch=fi.get();
            if(ch=='F')
            {
                ch=fi.get();
                if(ch=='F')
                {
                    tr=true;
                }
            }
        }
    }
    if(!tr)
    {
        cout<<"Неверный тип файла\n";
        return 0;
    }
    
    uint32_t stat[256];
    int i;
    for(i=0; i<256; i++)
    {
        fi.read((char * )&stat[i], 4);
        stat[i]=ntohl(stat[i]);
    }
    while(1)
    {
        ch=fi.get();
        if(!fi)
            break;
        cout<<ch;
    }
    shared_ptr < tree > beg(buildtree(stat));
    shared_ptr < tree > uk=beg;
        
}
