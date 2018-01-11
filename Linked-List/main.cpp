#include <iostream>

#include "Node.h"

using namespace std;

void push(int data, Node *& head);
void pushExpressive(int data, Node *& head);
void push(int data, Node ** head);
void pushExpressive(int data, Node ** head);
void printNodes(Node * head);
void printNodesExpressive(Node * head);
int length(Node * head);
int lengthExpressive(Node * head);
Node * buildWithSpecialCase(int data[], size_t numOfNodes);
Node * buildWithSpecialCaseUsingPush(int data[], size_t numOfNodes);

int main(int argc, char * argv[])
{
    int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Node * head = buildWithSpecialCaseUsingPush(data, 10);

    printNodes(head);

    cout << "The length of the linked list is: " << length(head) << endl;

    int x;
    cin >> x;
}

// This version of push is always safe
void push(int data, Node *& head)
{
    head = new Node(data, head);
}

// This version of push is always safe
void pushExpressive(int data, Node *& head)
{
    Node * newNode = new Node();

    newNode->data = data;
    newNode->next = head;

    head = newNode;
}

// This version of push is unsafe when passed the following:
// Node ** head = nullptr;
void push(int data, Node ** head)
{
    *head = new Node(data, *head);
}

// This version of push is unsafe when passed the following:
// Node ** head = nullptr;
void pushExpressive(int data, Node ** head)
{
    Node * newNode = new Node();

    newNode->data = data;
    newNode->next = *head;

    *head = newNode;
}

void printNodes(Node * head)
{
    int i = 0;
    while (head != nullptr)
    {
        cout << "Node " << i << ": " << head->data << endl;
        head = head->next;
        ++i;
    }
}

void printNodesExpressive(Node * head)
{
    Node * current = head;

    int i = 0;
    while (current != nullptr)
    {
        cout << "Node " << i << ": " << current->data << endl;
        current = current->next;
        ++i;
    }
}

int length(Node * head)
{
    int numOfNodes = 0;
    while (head != nullptr)
    {
        ++numOfNodes;
        head = head->next;
    }

    return numOfNodes;
}

int lengthExpressive(Node * head)
{
    int numOfNodes = 0;
    for(Node * current = head; current != nullptr; current = current->next)
    {
        ++numOfNodes;
    }

    return numOfNodes;
}

Node * buildWithSpecialCase(int data[], size_t numOfNodes)
{
    Node * head = nullptr;

    if (numOfNodes != 0)
    {
        head = new Node(data[0], nullptr);

        Node * tail = head;
        for (int i = 1; i < numOfNodes; ++i)
        {
            tail->next = new Node(data[i], nullptr);
            tail = tail->next;
        }
    }

    return head;
}

Node * buildWithSpecialCaseUsingPush(int data[], size_t numOfNodes)
{
    Node * head = nullptr;

    if (numOfNodes != 0)
    {
        push(data[0], head);

        Node * tail = head;
        for(int i = 1; i < numOfNodes; ++i)
        {
            push(data[i], tail->next);
            tail = tail->next;
        }
    }

    return head;
}
