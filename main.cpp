#include <iostream>
#include <memory>
#include <fstream>
using namespace std;

class tree
{
private:
    int uroven;  //потом убрать
    int weight;
    unsigned char c;
public:
    shared_ptr< tree > parent;
    shared_ptr< tree > left; //left son 
    shared_ptr< tree > right; //right son
    shared_ptr< tree > brother; //right brother
    tree() {uroven=1; weight=0; c=char(0); /*parent=NULL; left=NULL; right=NULL; brother=NULL;*/}
    tree(int u, int w,unsigned char ch, shared_ptr< tree > p, shared_ptr< tree > l, shared_ptr< tree > r, shared_ptr< tree > b) {uroven=u; weight=w; c=ch; parent=p; left=l; right=r; brother=b;}
    bool operator<(tree t);
    bool operator<=(tree t);
    friend ostream &operator<<(ostream &stream, tree t);
    int getWeight(){return weight;}
    int getUroven() {return uroven;}
    void setParent(shared_ptr< tree > p){parent=p;}
};

bool tree::operator<(tree t)
{
    if(weight<t.weight)
        return 1;
    else
        return 0;
}

bool tree::operator<=(tree t)
{
    if(weight<=t.weight)
        return 1;
    else
        return 0;
}

ostream &operator<<(ostream &stream, tree t)
{
    stream<<t.c<<' '<<t.weight;
    return stream;
}

int main(int argc, char** argv)
{
    if(argc<2)
    {
        cout<<"Нужно имя файла\n";
        return 0;
    }
    int i;
    int stat[256];
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
    shared_ptr< tree > uk;
    shared_ptr< tree > bro;
    for(i=255; i>=0; i--)
    {
        if(stat[i]>0)
        {
        cout<<i<<' '<<char(i)<<' '<<stat[i]<<endl;
        uk=shared_ptr< tree >(new tree(1, stat[i], char(i), shared_ptr< tree >(),  shared_ptr< tree >(),  shared_ptr< tree >(), bro));
        bro=uk;
        }
    }
    shared_ptr< tree > zap; //zapasnoi ukazatel
    shared_ptr< tree > beg=uk;
    shared_ptr< tree > min1, min2;
    cout<<"balak";
    while(1) //building tree
    {
    cout<<"vikkk";
        if(!beg->brother)
        {
            break;
        }
        min1=beg;
        uk=beg;
        while(1)
        {
            if(uk->brother)
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
    }
    uk=beg;
    /*while(1)
    {
        if()    
    }//write uahaha
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