#include <iostream>

#include "Node.h"

using namespace std;

bool lookup(Node * root, int target);
void insert(Node *& root, int data);
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

void printTree(Node * root)
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

        printTree(root->left);
        printTree(root->right);
    }
}
