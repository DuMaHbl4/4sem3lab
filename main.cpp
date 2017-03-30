#include <iostream>
#include <memory>
#include <fstream>
#include <string>
#include <netinet/in.h>
#include "builtree.h"
#include "recoder.h"
#include "tree.h"

using namespace std;

int main(int argc, char** argv)
{
    if(argc<2)
    {
        cout<<"Нужно имя файла\n";
        return 0;
    }
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
    for(i=255; i>=0; i--)
    {
        //if(stat[i]>0)
        //{
        cout<<i<<' '<<char(i)<<' '<<stat[i]<<endl;
        uk=shared_ptr< tree >(new tree(1, stat[i], char(i), shared_ptr< tree >(),  shared_ptr< tree >(),  shared_ptr< tree >(), bro));
        bro=uk;
        //}
    }
    
    shared_ptr< tree > zap; //zapasnoi ukazatel
    shared_ptr< tree > beg=uk;
    shared_ptr< tree > min1, min2;
    beg=shared_ptr< tree > (buildtree(stat));
    /*while(1) //building tree
    {
        if(!beg->brother)
        {
            break;
        }
        min1=beg;
        uk=beg;
        while(1)
        {
            if(!uk->brother)
                break;
            if(*(uk->brother.get())<*(min1.get()))
            {
                min1=uk->brother;    
            }
            uk=uk->brother;    
        }
        uk=beg;
        if(min1==beg)
            min2=beg->brother;
        else
            min2=beg;
        while(1)
        {
            if(!uk->brother)
                break;
            if(uk->brother!=min1)
            {
                if(*(uk->brother.get())<*(min2.get()))
                {
                    min2=uk->brother;    
                }
            }
            uk=uk->brother;
        }
        cout<<"min1 "<<*(min1.get())<<"min2"<<' '<<*(min2.get())<<endl;
        uk=beg;
        if(beg==min1)
        {
            cout<<"Объединили вначале "<<*(min1.get())<<' '<<*(min2.get())<<endl;
            zap=shared_ptr< tree > (new tree(min1->getUroven()+min2->getUroven(), min1->getWeight()+min2->getWeight(), char(0), shared_ptr< tree > (), min1, min2, beg->brother));
            beg=zap;
            min1->setParent(zap);
            min2->setParent(zap);
            zap=beg;
            uk=zap;
        }
        else
        {
            while(uk->brother!=min1)
            {
                uk=uk->brother;
                cout<<*(uk.get())<<endl;
            }
            cout<<"Не в начале "<<*(min1.get())<<' '<<*(min2.get())<<endl;
            zap=shared_ptr< tree > (new tree(min1->getUroven()+min2->getUroven(), min1->getWeight()+min2->getWeight(), 
                                    char(0), shared_ptr< tree >(), min1, min2, uk->brother->brother));
            uk->brother=zap;
            min1->setParent(zap);
            min2->setParent(zap);

            uk=beg;    
        }    
        while(uk->brother!=min2)
        {
            uk=uk->brother;
        }
        uk->brother=uk->brother->brother;
        uk=beg;
        while(1)
        {
            if(!uk)
                break;
            cout<<*(uk.get())<<endl;
            uk=uk->brother;        
        }
    }*/
    
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
    unsigned char ch;
    ifstream f(argv[1], ios::binary);
    ofstream archive("out.txt");
    archive<<"HUFF";
    uint32_t k;
    for(i=0; i<256; i++)
    {
        k=htonl(stat[i]);
        archive.write((char*)&k, 4);    
    }
    recoder rec(&archive);
    while(1)
    {
        //cout<<ch;
        ch=f.get();
        if(!f)
        {
            rec.end();
            break;
        }
        //cout<<ch<<symbol[ch]<<' ';
        rec.write(symbol[ch]);
    }    
    /*for(i=0; i<256; i++)
    {
        cout<<char(i)<<symbol[i]<<endl;
    }*/ 
    /*int gok;//delete this sheet
    uk=beg;
    while(1)
    {
        cout<<"ZZZZZPPPEERTGhgjkhgf";
        cin>>gok;
        if(gok==0)
            uk=uk->left;
        else if(gok==1)
            uk=uk->right;
        else
        {
            uk=uk->parent;
            if(uk==NULL)
                break;
        }
        if(uk->right==NULL)
        {
            cout<<"The end\n";
        }
        cout<<(*uk)<<endl;
    }
    /*while(1)//get new kods of symbols
    {
    if()    
    }*/
}
