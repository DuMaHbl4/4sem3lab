#include "tree.h"

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

