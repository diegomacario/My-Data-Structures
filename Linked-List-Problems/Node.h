#ifndef NODE_H
#define NODE_H

struct Node
{
    Node();
    Node(int data, Node * next);
    ~Node();

    int data;
    Node * next;
};

#endif // NODE_H
