#include <iostream>

#include "Node.h"

using namespace std;

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
}
