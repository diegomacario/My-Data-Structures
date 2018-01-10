#ifndef NODE_H
#define NODE_H

struct Node
{
    Node();
    Node(int data, Node * left, Node * right);
    ~Node();

    int data;
    Node * left;
    Node * right;
};

#endif // NODE_H
