#include <iostream>
#include <vector>

#include "Node.h"

using namespace std;

bool lookup(Node * root, int target);
void insert(Node *& root, int data);
void myPrintTree(Node * root);
int  size(Node * root);
int  maxDepth(Node * root);
int  minValue(Node * root);
void printTree(Node * root);
void printPostorder(Node * root);
void printPathsHelper(Node * node, vector<int> path);
void printPaths(Node * root);
void mirror(Node * root);
void doubleTree(Node * root);
bool sameTree(Node * a, Node * b);
int  countTrees(int numKeys);
int  minValueHelper(Node * root);
int  maxValueHelper(Node * root);
int  isBST(Node * root);

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

    myPrintTree(root);
    cout << "size: " << size(root) << endl;
    cout << "maxDepth: " << maxDepth(root) << endl;
    cout << "minValue: " << minValue(root) << endl;
    cout << "printTree:"<< endl;
    printTree(root);
    cout << endl;
    cout << "printPostorder:"<< endl;
    printPostorder(root);
    cout << endl;
    cout << "printPaths:"<< endl;
    printPaths(root);
    //cout << "mirror:"<< endl;
    //mirror(root);
    //printPaths(root);

    Node n1(1, nullptr, nullptr);
    Node n2(3, nullptr, nullptr);
    Node n3(2, &n1, &n2);
    Node * root2 = &n3;

    cout << "doubleTree1:"<< endl;
    doubleTree(root2);
    printPaths(root2);

    Node n4(1, nullptr, nullptr);
    Node n5(3, nullptr, nullptr);
    Node n6(2, &n4, &n5);
    Node * root3 = &n6;

    cout << "doubleTree2:"<< endl;
    doubleTree(root3);
    printPaths(root3);

    cout << "Are doubleTree1 and doubleTree2 equal? " << sameTree(root2, root3) << endl;

    cout << "minValueHelper: " << minValueHelper(root) << endl;
    cout << "maxValueHelper: " << maxValueHelper(root) << endl;
    cout << "isBST: " << isBST(root) << endl;

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

    printTree(root->left);

    cout << root->data << ' ';

    printTree(root->right);
}

// Problem 6: printPostorder
// Given a binary tree
void printPostorder(Node * root)
{
    if (root == nullptr)
    {
        return;
    }

    printPostorder(root->left);

    printPostorder(root->right);

    cout << root->data << ' ';
}

// Problem 7: hasPathSum
// Root-to-leaf path: sequence of nodes starting with the root node and proceeding downward to a leaf
// Return true if the binary tree has a root-to-leaf path that results in the given sum
int hasPathSum(Node * root, int sum)
{
    if (root == nullptr)
    {
        return (sum == 0);
    }

    int subSum = sum - root->data;

    return (hasPathSum(root->left, subSum) || hasPathSum(root->right, subSum));
}

// Problem 8: printPaths
// Print all the root-to-leaf paths
void printPathsHelper(Node * node, vector<int> path)
{
    // Add data of node to path array
    // If node->left && node->right are both null, print the contents of the array
    // If the left node is not null, call printPathsHelper with node->left
    // If the right node is not null, call printPathsHelper with node->right
    path.push_back(node->data);

    if (node->left == nullptr && node->right == nullptr)
    {
        for (vector<int>::iterator it = path.begin(); it != path.end(); ++it)
        {
            cout << *it << ' ';
        }
        cout << endl;

        return;
    }

    if (node->left != nullptr)
    {
        printPathsHelper(node->left, path);
    }

    if (node->right != nullptr)
    {
        printPathsHelper(node->right, path);
    }
}

void printPaths(Node * root)
{
    if (root == nullptr)
    {
        return;
    }

    vector<int> path; // We need this to persist

    printPathsHelper(root, path);
}

// Problem 9: mirror
void mirror(Node * root)
{
    if (root == nullptr)
    {
        return;
    }

    Node * temp = root->left;
    root->left = root->right;
    root->right = temp;

    mirror(root->left);
    mirror(root->right);
}

// Problem 10: doubleTree
void doubleTree(Node * root)
{
    if (root == nullptr)
    {
        return;
    }

    Node * newNode = new Node(root->data, root->left, nullptr);
    root->left = newNode;

    doubleTree(newNode->left);
    doubleTree(root->right);
}

// Problem 11: sameTree
bool sameTree(Node * a, Node * b)
{
    if (a == nullptr && b == nullptr)
    {
        return true;
    }
    else if (a != nullptr && b != nullptr)
    {
        if (a->data == b->data)
        {
            return (sameTree(a->left, b->left) && sameTree(a->right, b->right));    
        }
        else
        {
            return false; // The data contained by the nodes is not the same
        }
    }
    else
    {
        return false; // One is null and the other isn't
    }
}

// Problem 12: countTree
// Suppose you are building an N node binary search tree with the values 1..N.
// How many structurally different binary search trees are there that store those values?
int countTrees(int numKeys)
{
    if (numKeys <= 1)
    {
        return 1;
    }

    int left, right;
    int sum = 0;

    for (int root = 1; root <= numKeys; ++root)
    {
        left = countTrees(root - 1);
        right = countTrees(numKeys - root);
        sum += left * right;
    }

    return sum;
}

// Problem 13: isBST
// Assume you have the helper functions minValue() and maxValue(), which return
// the min or max value for a non-empty tree.
int minValueHelper(Node * root)
{
    if (root == nullptr)
    {
        return 0;
    }

    int min = root->data;

    if (root->left != nullptr)
    {
        int minLeft = minValueHelper(root->left);

        if (minLeft < min)
        {
            min = minLeft;
        }
    }

    if (root->right != nullptr)
    {
        int minRight = minValueHelper(root->right);

        if (minRight < min)
        {
            min = minRight;
        }
    }

    return min;
}

int maxValueHelper(Node * root)
{
    if (root == nullptr)
    {
        return 0;
    }

    int max = root->data;

    if (root->left != nullptr)
    {
        int maxLeft = maxValueHelper(root->left);

        if (maxLeft > max)
        {
            max = maxLeft;
        }
    }

    if (root->right != nullptr)
    {
        int maxRight = maxValueHelper(root->right);

        if (maxRight > max)
        {
            max = maxRight;
        }
    }

    return max;
}

int isBST(Node * root)
{
    if (root == nullptr)
    {
        return true;
    }

    if ((root->left != nullptr) &&
        (root->data < minValueHelper(root->left)))
    {
        return false;
    }

    if ((root->right != nullptr) &&
        (root->data >= maxValueHelper(root->right)))
    {
        return false;
    }

    return (isBST(root->left) && isBST(root->right));
}
