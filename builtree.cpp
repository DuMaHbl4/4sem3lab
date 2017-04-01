#include <iostream>
#include <memory>
#include "builtree.h"
		
using namespace std;
		
tree* buildtree(uint32_t* stat)
{
		int i;
		shared_ptr< tree > uk;
    shared_ptr< tree > bro;
    for(i=255; i>=0; i--)
    {
        //if(stat[i]>0)
        //{
        //cout<<i<<' '<<char(i)<<' '<<stat[i]<<endl;
        uk=shared_ptr< tree >(new tree(1, stat[i], char(i), shared_ptr< tree >(),  shared_ptr< tree >(),  shared_ptr< tree >(), bro));
        bro=uk;
        //}
    }
    
    shared_ptr< tree > zap; //zapasnoi ukazatel
    shared_ptr< tree > beg=uk;
    shared_ptr< tree > min1, min2;
    while(1) //building tree
    {
        if(!beg->brother)
        {
            break;
        }
        min1=beg;
        uk=beg;
        cout<<*(uk.get())<<endl;
        while(1)
        {
            if(!uk->brother)
                break;
            if(*(uk->brother.get())<*(min1.get()))
            {
                min1=uk->brother;    
            }
            uk=uk->brother;    
            cout<<*(uk.get())<<endl;
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
        //cout<<"min1 "<<*(min1.get())<<"min2"<<' '<<*(min2.get())<<endl;
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
                //cout<<*(uk.get())<<endl;
            }
            cout<<"Не в начале "<<*(min1.get())<<' '<<*(min2.get())<<endl;
            zap=shared_ptr< tree > (new tree(min1->getUroven()+min2->getUroven(), min1->getWeight()+min2->getWeight(), 
                                    char(0), shared_ptr< tree >(), min1, min2, uk->brother->brother));
            uk->brother=zap;
            min1->setParent(zap);
            min2->setParent(zap);

            uk=beg;    
        }
        if(min2==beg)
        {
            beg=beg->brother;
        }   
        else
        { 
            while(uk->brother!=min2)
            {
                uk=uk->brother;
            }
        }
        uk->brother=uk->brother->brother;
        uk=beg;
        /*while(1)
        {
            if(!uk)
                break;
            cout<<*(uk.get())<<endl;
            uk=uk->brother;        
        }*/
    }
    return beg.get();
}
