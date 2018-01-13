#include <iostream>
#include <assert.h>

#include "Node.h"

using namespace std;

Node * buildLinkedList(int data[], size_t numNodes);
void   printNodes(Node * head);
int    length(Node * head);
int    Count(Node * head, int searchFor);
int    GetNth(Node * head, int index);
void   DeleteList(Node *& head);
int    Pop(Node *& head);
void   InsertNth(Node *& head, int index, int data);
void   SortedInsert(Node *& head, Node * newNode);

int main(int argc, char * argv[])
{
    int data[10] = {1, 2, 3, 4, 6, 7, 8, 9, 10, 11};
    Node * head = buildLinkedList(data, 10);

    cout << "Original linked list:" << endl;
    printNodes(head);

    cout << "Sorted insert 0:" << endl;
    Node * newNode1 = new Node(0, nullptr);
    SortedInsert(head, newNode1);
    printNodes(head);

    cout << "Sorted insert 5:" << endl;
    Node * newNode2 = new Node(5, nullptr);
    SortedInsert(head, newNode2);
    printNodes(head);

    cout << "Sorted insert 9:" << endl;
    Node * newNode3 = new Node(9, nullptr);
    SortedInsert(head, newNode3);
    printNodes(head);

    cout << "Sorted insert 12:" << endl;
    Node * newNode4 = new Node(12, nullptr);
    SortedInsert(head, newNode4);
    printNodes(head);

    cout << "The value at index 0 is: " << GetNth(head, 0) << endl;
    cout << "Pop 0: " << Pop(head) << endl;
    cout << "The length of the linked list is: " << length(head) << endl;

    DeleteList(head);

    int x;
    cin >> x;

    return 0;
}

Node * buildLinkedList(int data[], size_t numNodes)
{
    if (numNodes == 0)
    {
        return nullptr;
    }
    
    Node * head = new Node(data[0], nullptr);

    Node * current = head;
    for (int i = 1; i < numNodes; ++i)
    {
        current->next = new Node(data[i], nullptr);
        current = current->next;
    }

    return head;
}

void printNodes(Node * head)
{
    Node * current = head;

    int count = 0;
    while (current != nullptr)
    {
        cout << "Node " << count << ": " << current->data << endl;
        ++count;
        current = current->next;
    }
}

int length(Node * head)
{
    Node * current = head;

    int count = 0;
    while (current != nullptr)
    {
        ++count;
        current = current->next;
    }

    return count;
}

// Problem 1: Count
int Count(Node * head, int searchFor)
{
    Node * current = head;

    int timesNumOccurs = 0;
    while (current != nullptr)
    {
        if (current->data == searchFor)
        {
            ++timesNumOccurs;
        }
        current = current->next;
    }

    return timesNumOccurs;
}

// Problem 2: GetNth
// The range of the index is [0, length - 1]
int GetNth(Node * head, int index)
{
    assert(index >= 0 && "Requested index is negative.");

    Node * current = head;

    int count = 0;
    while (current != nullptr)
    {
        if (count == index)
        {
            return current->data;
        }

        ++count;
        current = current->next;
    }

    assert(0 && "Requested index is not in the range [0, length - 1].");
}

// Problem 3: DeleteList
void DeleteList(Node *& head)
{
    Node * current = head;
    Node * nextNode;

    while (current != nullptr)
    {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }

    head = nullptr;
}

// Problem 4: Pop
int Pop(Node *& head)
{
    assert(head != nullptr && "Cannot pop an empty linked list.");

    Node * newHead = head->next;
    int headData = head->data;

    delete head;
    head = newHead;

    return headData;
}

// Problem 5: InsertNth
// The range of the index is [0, length]
void InsertNth(Node *& head, int index, int data)
{
    assert(index >= 0 && "Requested index is negative.");

    if (index == 0 && head == nullptr)
    {
        head = new Node(data, nullptr);
        return;
    }
    else if (index == 0)
    {
        head = new Node(data, head->next);
        return;
    }
    else
    {
        Node * current = head;
        int count = 0;
        
        while (current != nullptr)
        {
            if (count == index - 1)
            {
                Node * postNode = current->next;
                current->next = new Node(data, postNode);
                return;
            }

            ++count;
            current = current->next;
        }
    }

    assert(0 && "Requested index is not in the range [0, length].");
}

// Problem 6: SortedInsert
// Linked list must already be sorted in increasing order
void SortedInsert(Node *& head, Node * newNode)
{
    if (head == nullptr || (newNode->data <= head->data))
    {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node * prevNode = head;
    Node * postNode = head->next;

    while (postNode != nullptr)
    {
        if (newNode->data >= prevNode->data &&
            newNode->data <= postNode->data)
        {
            newNode->next = prevNode->next;
            prevNode->next = newNode;
            return;
        }

        prevNode = postNode;
        postNode = postNode->next;
    }

    prevNode->next = newNode;
}
