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
Node * buildWithDummyNode(int data[], size_t numOfNodes);
Node * buildWithDummyNodeUsingPush(int data[], size_t numOfNodes);
Node * buildWithLocalReference(int data[], size_t numOfNodes);

void appendNode(int data, Node *& head);
void appendNodeWithPush(int data, Node *& head);

Node * copyList(Node * head);
Node * copyListUsingPush(Node * head);
Node * copyListWithDummy(Node * head);
Node * copyListWithDummyUsingPush(Node * head);
Node * copyListWithLocalReference(Node * head);
Node * copyListRecursive(Node * head);

int main(int argc, char * argv[])
{
    int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Node * head = buildWithLocalReference(data, 10);

    appendNode(11, head);
    appendNode(12, head);

    Node * copy = copyListRecursive(head);

    printNodes(copy);

    cout << "The length of the linked list is: " << length(copy) << endl;

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

Node * buildWithDummyNode(int data[], size_t numOfNodes)
{
    Node dummy;
    Node * tail = &dummy;

    for (int i = 0; i < numOfNodes; ++i)
    {
        tail->next = new Node(data[i], nullptr);
        tail = tail->next;
    }

    return dummy.next;
}

Node * buildWithDummyNodeUsingPush(int data[], size_t numOfNodes)
{
    Node dummy;
    Node * tail = &dummy;

    for (int i = 0; i < numOfNodes; ++i)
    {
        push(data[i], tail->next);
        tail = tail->next;
    }

    return dummy.next;
}

Node * buildWithLocalReference(int data[], size_t numOfNodes)
{
    Node * head;
    Node ** tailPtr = &head;

    for (int i = 0; i < numOfNodes; ++i)
    {
        *tailPtr = new Node(data[i], nullptr);
        tailPtr = &((*tailPtr)->next);
    }

    return head;
}

void appendNode(int data, Node *& head)
{
    if (head == nullptr)
    {
        head = new Node(data, nullptr);
    }
    else
    {
        Node * current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }

        current->next = new Node(data, nullptr);
    }
}

void appendNodeWithPush(int data, Node *& head)
{
    if (head == nullptr)
    {
        push(data, head);
    }
    else
    {
        Node * current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }

        push(data, current->next);
    }
}

Node * copyList(Node * head)
{
    if (head == nullptr)
    {
        return nullptr;
    }

    Node * newHead = new Node(head->data, nullptr); // Always points to the head of the new linked list
    Node * tail    = newHead;                       // Always points to the tail of the new linked list
    Node * current = head;                          // Used to iterate over the linked list that is being copied

    while (current->next != nullptr)
    {
        current = current->next;
        tail->next = new Node(current->data, nullptr);
        tail = tail->next;
    }

    return newHead;
}

Node * copyListUsingPush(Node * head)
{
    if (head == nullptr)
    {
        return nullptr;
    }

    Node * newHead = nullptr; // Always points to the head of the new linked list
    push(head->data, newHead);

    Node * tail    = newHead; // Always points to the tail of the new linked list
    Node * current = head;    // Used to iterate over the linked list that is being copied

    while (current->next != nullptr)
    {
        current = current->next;
        push(current->data, tail->next);
        tail = tail->next;
    }

    return newHead;
}

Node * copyListWithDummy(Node * head)
{
    Node dummy;

    Node * tail = &dummy;
    Node * current = head;

    while (current != nullptr)
    {
        tail->next = new Node(current->data, nullptr);
        tail = tail->next;
        current = current->next;
    }

    return dummy.next;
}

Node * copyListWithDummyUsingPush(Node * head)
{
    Node dummy;
    Node * tail = &dummy;
    Node * current = head;

    while (current != nullptr)
    {
        push(current->data, tail->next);
        tail = tail->next;
        current = current->next;
    }

    return dummy.next;
}

Node * copyListWithLocalReference(Node * head)
{
    Node * newHead = nullptr;
    Node ** tailPtr = &newHead;
    Node * current = head;

    while (current != nullptr)
    {
        *tailPtr = new Node(current->data, nullptr);
        tailPtr = &((*tailPtr)->next);
        current = current->next;
    }

    return newHead;
}

// This version uses stack space proportional to the length of the list
Node * copyListRecursive(Node * head)
{
    if (head == nullptr)
    {
        return nullptr;
    }
    else
    {
        Node * newNode = new Node(head->data, nullptr);
        newNode->next = copyListRecursive(head->next);
        return newNode;
    }
}
