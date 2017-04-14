#include <fstream>
#include <iostream>
#include <memory>
#include "builtree.h"
		
using namespace std;
		
tree* buildtree(uint32_t* stat)
{
    ofstream co("3.txt");
		int i;
		shared_ptr< tree > uk;
    shared_ptr< tree > bro;
    for(i=255; i>=0; i--)
    {
        uk=shared_ptr< tree >(new tree(1, stat[i], char(i), shared_ptr< tree >(),  shared_ptr< tree >(),  shared_ptr< tree >(), bro));
        bro=uk;
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
        uk=beg;
        if(beg==min1)
        {
            beg=beg->brother;
        }
        else
        {
            while(uk->brother!=min1)
            {
                uk=uk->brother;
            }
            uk->brother=uk->brother->brother;   
        }
        if(min2==beg)
        {
            beg=beg->brother;
        }   
        else
        { 
            uk=beg;
            while(uk->brother!=min2)
            {
                uk=uk->brother;
            }
            uk->brother=uk->brother->brother;
        }
        zap=shared_ptr< tree > (new tree(min1->getUroven()+min2->getUroven(), min1->getWeight()+min2->getWeight(), 
                                    char(0), shared_ptr< tree >(), min1, min2, beg));
        beg=zap;
        min1->setParent(zap);
        min2->setParent(zap);
    }
    return beg.get();
}
