#include <iostream>
#include <memory>
#include <fstream>
#include <string>
#include <netinet/in.h>
#include "builtree.h"
#include "recoder.h"
#include "tree.h"
#include "encoder.h"

using namespace std;

int main(int argc, char** argv)
{
if(argc<3)
{
    cout<<"Требуемый формат: ./main in.txt -c out.txt\n";
    return 0;
}
if(argv[2][0]=='-')
{
    if(argv[2][1]=='c')
    {
        int i;
        uint32_t stat[256]; //встречаемость
        for(i=0; i<256; i++)
            stat[i]=0;
        unsigned char c;
        ifstream fi(argv[1] , ios::binary);
        while(1)
        {
            c=fi.get();
            if(!fi)
                    break;
            stat[c]++;
        }   
        fi.close();
        shared_ptr< tree > uk;
        shared_ptr< tree > bro;
        shared_ptr< tree > zap; //zapasnoi ukazatel
        shared_ptr< tree > beg=uk;
        shared_ptr< tree > min1, min2;
        beg=shared_ptr< tree > (buildtree(stat));
        
        uk=beg;
        bool up=false; //true если идем по дереву вверх
        string symbol[256]; //новая кодировка символа
        string seq; //перходы
        while(1) //obhod
        {
            if(up)
            {
                if(uk->parent)
                    uk=uk->parent;
                else
                    break;
                if(seq.back()=='0')
                {
                    seq.pop_back();
                    uk=uk->right;
                    seq.push_back('1');
                    up=false;
                }
                else
                {
                    seq.pop_back();
                }
            }
            else
            {
                if(uk->left)
                {
                    uk=uk->left;
                    seq.push_back('0');    
                }
                else
                {
                    symbol[uk->getC()]=seq;
                    up=true;    
                }
            }    
        }
        unsigned int bt=1028;
        unsigned char ch;
        ifstream f(argv[1], ios::binary);
        ofstream archive(argv[3]);
        /*archive.put('H');
        archive.put('U');
        archive.put('F');
        archive.put('F');*/
        archive.write("HUFF",4);
        uint32_t k;
        for(i=0; i<256; i++)
        {
            k=htonl(stat[i]);
            archive.write((char*)&k, 4);    
        }
        recoder rec(&archive);
        while(1)
        {
            ch=f.get();
            //cout<<ch;
            //cout<<symbol[ch]<<' ';
            if(!f)
            {
                rec.end();
                break;
            }
            rec.write(symbol[ch]);
        }
        bt=rec.las+bt;    
        /*for(i=0; i<256; i++)
        {
            cout<<i<<' '<<symbol[i]<<endl;
        }*/
        cout<<"Я должен записать "<<bt<<" байт"; 
    }
    else if(argv[2][1]=='d')
    {
        unsigned int st=0;
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
            cout<<stat[i]<<endl;
            st=st+stat[i];
        }
        cout<<"4islo simvolov = "<<st<<endl;
        shared_ptr < tree > beg(buildtree(stat));
        shared_ptr < tree > uk=beg;
        bool go=false;
        int step;
        ofstream out(argv[3]);
        string hh;
        int k=0;
        unsigned char t;
        while(k)
        {
            k--;
            t=fi.get();
            if(!fi)
                break;
            cout<<(int)t<<' ';
        }
        //t=fi.get();
        //t=fi.get();
        encoder res(&fi);
        while(!go)
        {
            uk=beg;
            while(1)
            {
                step=res.getBit();
                if(step==-1)
                {
                    cout<<"Step=-1 ";
                    go=true;
                    break;
                }
                else
                {
                    if(step==0)
                    {	
                        hh.push_back('0');
                        //cout<<"step=0 "; 
                        uk=uk->left;
                    }    
                    else
                    {	
                        hh.push_back('1');
                        //cout<<"step=1 ";
                        uk=uk->right;
                    }
                    if(uk->left==NULL)
                    {
                        cout<<uk->getC();
                        hh.clear();
                        out.put(uk->getC());
                        break;
                    }
                }
            }
        }            
    }
    else
    {
        cout<<"Неверный ключ. -c - кодировать: -d - распаковать";
        return 0;
    }
}
else
{
    cout<<"Неверный ключ. -c - кодировать: -d - распаковать";
        return 0;
}
}
