#include "Node.h"

Node::Node()
    : data(0)
    , left(nullptr)
    , right(nullptr)
{

}

Node::Node(int data, Node * left, Node * right)
    : data(data)
    , left(left)
    , right(right)
{

}

Node::~Node()
{

}
