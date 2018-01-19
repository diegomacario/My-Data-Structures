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
void   SortedInsertWithDummy(Node *& head, Node * newNode);
void   SortedInsertWithLocalReference(Node *& head, Node * newNode);
void   InsertSort(Node *& head);
void   Append(Node *& headA, Node *& headB);
void   FrontBackSplit(Node * source, Node *& front, Node *& back);
void   FrontBackSplit2(Node * source, Node *& front, Node *& back);
void   RemoveDuplicates(Node * head);
void   RemoveDuplicates2(Node * head);
void   MoveNode(Node *& destination, Node *& source);
void   AlternatingSplit(Node * source, Node *& a, Node *& b);
Node * ShuffleMerge(Node * a, Node * b);
Node * ShuffleMerge2(Node * a, Node * b);
Node * SortedMerge(Node * a, Node * b);
Node * SortedMerge2(Node * a, Node * b);

int main(int argc, char * argv[])
{
    int data[10] = {1, 2, 3, 4, 6, 7, 8, 9, 10, 11};
    Node * head = buildLinkedList(data, 10);

    cout << "Original linked list:" << endl;
    printNodes(head);

    cout << "Sorted insert 0:" << endl;
    Node * newNode1 = new Node(0, nullptr);
    SortedInsertWithLocalReference(head, newNode1);
    printNodes(head);

    cout << "Sorted insert 5:" << endl;
    Node * newNode2 = new Node(5, nullptr);
    SortedInsertWithLocalReference(head, newNode2);
    printNodes(head);

    cout << "Sorted insert 9:" << endl;
    Node * newNode3 = new Node(9, nullptr);
    SortedInsertWithLocalReference(head, newNode3);
    printNodes(head);

    cout << "Sorted insert 12:" << endl;
    Node * newNode4 = new Node(12, nullptr);
    SortedInsertWithLocalReference(head, newNode4);
    printNodes(head);

    cout << "Sorted insert 0:" << endl;
    Node * newNode5 = new Node(0, nullptr);
    SortedInsertWithLocalReference(head, newNode5);
    printNodes(head);

    cout << "Sorted insert 12:" << endl;
    Node * newNode6 = new Node(12, nullptr);
    SortedInsertWithLocalReference(head, newNode6);
    printNodes(head);

    cout << "Insert sort:" << endl;
    int data2[12] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1};
    Node * head2 = buildLinkedList(data2, 12);
    cout << "Insert sort: Before" << endl;
    printNodes(head2);
    InsertSort(head2);
    cout << "Insert sort: After" << endl;
    printNodes(head2);

    cout << "Append:" << endl;
    Append(head, head2);
    printNodes(head);

    cout << "Front back split:" << endl;
    int data3[] = {1, 2, 3, 4, 5};
    Node * source = buildLinkedList(data3, 5);
    Node * front;
    Node * back;
    FrontBackSplit2(source, front, back);
    cout << "Front:" << endl;
    printNodes(front);
    cout << "Back:" << endl;
    printNodes(back);

    cout << "Remove duplicates:" << endl;
    int data4[] = {0, 0, 0, 1, 1, 1, 1, 2, 2, 3, 4, 4, 4, 4};
    Node * linkedListWithDuplicates = buildLinkedList(data4, 14);
    cout << "Before:" << endl;
    printNodes(linkedListWithDuplicates);
    cout << "After:" << endl;
    RemoveDuplicates2(linkedListWithDuplicates);
    printNodes(linkedListWithDuplicates);

    cout << "Move node:" << endl;
    int data5[] = {1, 3, 5, 7};
    int data6[] = {2, 4, 6, 8};
    Node * destForMove = buildLinkedList(data5, 4);
    Node * srcForMove = buildLinkedList(data6, 4);
    //MoveNode(destForMove, srcForMove);
    cout << "Dst:" << endl;
    printNodes(destForMove);
    cout << "Src:" << endl;
    printNodes(srcForMove);

    //cout << "Alternating split:" << endl;
    //Node * a;
    //Node * b;
    //cout << "Total:" << endl;
    //printNodes(destForMove);
    //AlternatingSplit(destForMove, a, b);
    //cout << "A:" << endl;
    //printNodes(a);
    //cout << "B:" << endl;
    //printNodes(b);

    cout << "Shuffle:" << endl;
    Node * shuffle = SortedMerge2(destForMove, srcForMove);
    printNodes(shuffle);

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
    // First node is a special case
    if (head == nullptr || newNode->data < head->data)
    {
        newNode->next = head;
        head = newNode;
        return;
    }

    // When we exit this loop, current points to the node after which
    // we should insert the new node
    Node * current = head;
    while (current->next != nullptr)
    {
        if (newNode->data < current->next->data)
        {
            break;
        }

        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

// Problem 6: SortedInsert (alternative solution)
// Linked list must already be sorted in increasing order
void SortedInsertWithDummy(Node *& head, Node * newNode)
{
    Node dummy(0, head);

    Node * current = &dummy;
    while (current->next != nullptr)
    {
        if (newNode->data < current->next->data)
        {
            break;
        }
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
    head = dummy.next;
}

// Problem 6: SortedInsert (alternative solution)
// Linked list must already be sorted in increasing order
void SortedInsertWithLocalReference(Node *& head, Node * newNode)
{
    Node ** currentRef = &head;
    while (*currentRef != nullptr)
    {
        if (newNode->data < (*currentRef)->data)
        {
            break;
        }
        currentRef = &((*currentRef)->next);
    }

    newNode->next = *currentRef;
    *currentRef = newNode;
}

// Problem 7: InsertSort
// Must use SortedInsert
void InsertSort(Node *& head)
{
    Node * newHead = nullptr;

    Node * current = head;
    Node * next;
    while (current != nullptr)
    {
        next = current->next;
        SortedInsert(newHead, current); // This function changes the next value of the node we pass to it
        current = next;
    }

    head = newHead;
}

// Problem 8: Append
void Append(Node *& headA, Node *& headB)
{
    if (headA == nullptr)
    {
        headA = headB;
        headB = nullptr;
        return;
    }

    Node * current = headA;
    while (current->next != nullptr)
    {
        current = current->next;
    }

    current->next = headB;
    headB = nullptr;
}

// Problem 9: FrontBackSplit
void FrontBackSplit(Node * source, Node *& front, Node *& back)
{
    if (source == nullptr)
    {
        front = nullptr;
        back = nullptr;
        return;
    }

    // Count the number of nodes in the source
    int count = 0;
    Node * current = source;
    while (current != nullptr)
    {
        ++count;
        current = current->next;
    }

    current = source;
    for (int i = 0; i < ((count / 2) - 1); ++i)
    {
        current = current->next;
    }

    if (count % 2 == 1) // Odd
    {
        // Advance one more step
        current = current->next;
    }

    front = source;
    back = current->next;
    current->next = nullptr;
}

// Problem 9: FrontBackSplit (alternative solution)
void FrontBackSplit2(Node * source, Node *& front, Node *& back)
{
    // Take care of 2 cases: empty linked list and linked list of length 1 
    if (source == nullptr || source->next == nullptr)
    {
        front = source;
        back = nullptr;
        return;
    }

    // Fast advances two steps for every step slow takes
    // If fast cannot advance or can only advance one step, slow does not advance
    Node * slow = source;
    Node * fast = source->next;

    while (fast != nullptr)
    {
        fast = fast->next;
        if (fast != nullptr)
        {
            fast = fast->next;
            slow = slow->next;
        }
    }

    front = source;
    back = slow->next;
    slow->next = nullptr;
}

// Problem 10: RemoveDuplicates
// Linked list must already be sorted in increasing order
void RemoveDuplicates(Node * head)
{
    if (head == nullptr)
    {
        return;
    }

    int currentValue;
    Node * current = head;
    Node * nextNode = nullptr;
    while (current != nullptr)
    {
        currentValue = current->data;
        nextNode = current->next;

        while (nextNode != nullptr && nextNode->data == currentValue)
        {
            current->next = nextNode->next;
            delete nextNode;
            nextNode = current->next;
        }

        current = nextNode;
    }
}

// Problem 10: RemoveDuplicates (alternative solution)
// Linked list must already be sorted in increasing order
void RemoveDuplicates2(Node * head)
{
    if (head == nullptr)
    {
        return;
    }

    Node * current = head;
    Node * nextNext = nullptr;
    while (current->next != nullptr)
    {
        if (current->data == current->next->data)
        {
            nextNext = current->next->next;
            delete current->next;
            current->next = nextNext;
        }
        else
        {
            current = current->next;
        }
    }
}

// Problem 11: MoveNode
void MoveNode(Node *& destination, Node *& source)
{
    if (source == nullptr)
    {
        return;
    }

    Node * newHeadOfSource = source->next;

    source->next = destination;
    destination = source;

    source = newHeadOfSource;
}

// Problem 12: AlternatingSplit
void AlternatingSplit(Node * source, Node *& a, Node *& b)
{
    if (source == nullptr)
    {
        a = nullptr;
        b = nullptr;
        return;
    }

    Node * current = source;
    a = current;
    current = current->next;
    b = current;

    if (current == nullptr)
    {
        return;
    }

    current = current->next;

    bool turnOfA = true;
    Node * currentA = a;
    Node * currentB = b;
    while (current != nullptr)
    {
        if (turnOfA)
        {
            currentA->next = current;
            currentA = currentA->next;
            current = current->next;
            turnOfA = false;
        }
        else
        {
            currentB->next = current;
            currentB = currentB->next;
            current = current->next;
            turnOfA = true;
        }
    }

    currentA->next = nullptr;
    currentB->next = nullptr;
}

// Problem 13: ShuffleMerge
Node * ShuffleMerge(Node * a, Node * b)
{
    if (a == nullptr)
    {
        return b;
    }

    Node * currentA = a;
    Node * currentB = b;
    Node * headShuffled = nullptr;
    Node * currentShuffled = nullptr;

    MoveNode(headShuffled, currentA);
    currentShuffled = headShuffled;

    while (currentA != nullptr || currentB != nullptr)
    {
        if (currentB != nullptr)
        {
            MoveNode(currentShuffled->next, currentB);
            currentShuffled = currentShuffled->next;
        }
        if (currentA != nullptr)
        {
            MoveNode(currentShuffled->next, currentA);
            currentShuffled = currentShuffled->next;
        }
    }

    return headShuffled;
}

// Problem 13: ShuffleMerge (alternative solution)
Node * ShuffleMerge2(Node * a, Node * b)
{
    Node dummy;
    Node * tail = &dummy;
    dummy.next = nullptr;

    while (1)
    {
        if (a == nullptr)
        {
            tail->next = b;
            break;
        }
        else if (b == nullptr)
        {
            tail->next = a;
            break;
        }
        else
        {
            tail->next = a;
            tail = tail->next;
            a = a->next;

            tail->next = b;
            tail = tail->next;
            b = b->next;
        }
    }

    return(dummy.next);
}

// Problem 14: SortedMerge
Node * SortedMerge(Node * a, Node * b)
{
    Node dummy;
    Node * current = &dummy;

    while (true)
    {
        if (a == nullptr)
        {
            current->next = b;
            break;
        }
        else if (b == nullptr)
        {
            current->next = a;
            break;
        }
        else if (a->data <= b->data)
        {
            current->next = a;
            current = current->next;
            a = a->next;
        }
        else if (b->data < a->data) // This could just an else statement
        {
            current->next = b;
            current = current->next;
            b = b->next;
        }
    }

    return dummy.next;
}

// Problem 14: SortedMerge (alternative solution)
Node * SortedMerge2(Node * a, Node * b)
{
    Node * head;
    Node ** tail = &head;

    while (true)
    {
        if (a == nullptr)
        {
            *tail = b;
            break;
        }
        else if (b == nullptr)
        {
            *tail = a;
            break;
        }
        else if (a->data <= b->data)
        {
            *tail = a;
            tail = &((*tail)->next);
            a = a->next;
        }
        else
        {
            *tail = b;
            tail = &((*tail)->next);
            b = b->next;
        }
    }

    return head;
}
