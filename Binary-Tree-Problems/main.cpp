#include <iostream>

#include "Node.h"

using namespace std;

bool lookup(Node * root, int target);
void insert(Node *& root, int data);
void myPrintTree(Node * root);
int  size(Node * root);
int  maxDepth(Node * root);
int  minValue(Node * root);
void printTree(Node * root);

int main(int argc, char * argv[])
{
    // First floor
    Node node1(1, nullptr, nullptr);
    Node node2(4, nullptr, nullptr);
    Node node3(6, nullptr, nullptr);
    
    // Second floor
    Node node4(3, &node1, &node2);
    Node node5(9, &node3, nullptr);
    
    // Third floor
    Node node6(5, &node4, &node5);
    
    // Root
    Node * root = &node6;

    cout << "lookup(1): " << lookup(root, 1) << endl;
    cout << "lookup(5): " << lookup(root, 5) << endl;
    cout << "lookup(2): " << lookup(root, 2) << endl;
    cout << "lookup(11): " << lookup(root, 11) << endl;

    insert(root, 7);
    insert(root, 10);
    insert(root, 2);
    //insert(root, -1);
    //insert(root, -2);

    myPrintTree(root);
    cout << "size: " << size(root) << endl;
    cout << "maxDepth: " << maxDepth(root) << endl;
    cout << "minValue: " << minValue(root) << endl;
    cout << "printTree:"<< endl;
    printTree(root);

    int x;
    cin >> x;
}

// Searches for given value in BST
bool lookup(Node * root, int target)
{
    if (root == nullptr)
    {
        return false;
    }
    else if (root->data == target)
    {
        return true;
    }
    else if (target < root->data)
    {
        return lookup(root->left, target);
    }
    else // target > root->data
    {
        return lookup(root->right, target);
    }
}

// Inserts given value in BST
void insert(Node *& root, int data)
{
    if (root == nullptr)
    {
        root = new Node(data, nullptr, nullptr);
    }
    else if (data <= root->data)
    {
        insert(root->left, data);
    }
    else // data > root->data
    {
        insert(root->right, data);
    }
}

void myPrintTree(Node * root)
{
    if (root == nullptr)
    {
        return;
    }
    else
    {
        if (root->left != nullptr)
        {
            cout << root->left->data << ", ";
        }
        else
        {
            cout << "null" << ", ";
        }

        cout << root->data;

        if (root->right != nullptr)
        {
            cout << ", " << root->right->data;
        }
        else
        {
            cout << ", " << "null";
        }

        cout << endl;

        myPrintTree(root->left);
        myPrintTree(root->right);
    }
}

// Problem 1: build123
Node * build123()
{
    Node * root = new Node(2, nullptr, nullptr);
    root->left = new Node(1, nullptr, nullptr);
    root->right = new Node(3, nullptr, nullptr);
    return root;
}

// Problem 2: size
int size(Node * root)
{
    if (root == nullptr)
    {
        return 0;
    }
    else
    {
        return size(root->left) + 1 + size(root->right);
    }
}

// Problem 3: maxDepth
// Given a binary tree
int maxDepth(Node * root)
{
    if (root == nullptr)
    {
        return 0;
    }

    int leftDepth = maxDepth(root->left);
    int rightDepth = maxDepth(root->right);

    if (leftDepth >= rightDepth)
    {
        return (leftDepth + 1);
    }
    else
    {
        return (rightDepth + 1);
    }
}

// Problem 4: minValue
// Given a binary search tree
int minValue(Node * root)
{
    if (root == nullptr)
    {
        return 0;
    }

    if (root->left == nullptr)
    {
        return root->data;
    }
    else
    {
        return minValue(root->left);
    }
}

// Problem 5: printTree
// Given a binary search tree
void printTree(Node * root)
{
    if (root == nullptr)
    {
        return;
    }

    if (root->left != nullptr)
    {
        printTree(root->left);
    }

    cout << root->data << ' ';

    if (root->right != nullptr)
    {
        printTree(root->right);
    }
}
