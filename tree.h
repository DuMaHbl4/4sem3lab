#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <memory>
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
    unsigned char getC() {return c;}
    void setParent(shared_ptr< tree > p){parent=p;}
};

#endif
