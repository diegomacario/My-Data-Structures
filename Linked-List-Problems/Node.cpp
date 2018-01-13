#include "Node.h"

Node::Node()
    : data(0)
    , next(nullptr)
{

}

Node::Node(int data, Node * next)
    : data(data)
    , next(next)
{

}

Node::~Node()
{

}
