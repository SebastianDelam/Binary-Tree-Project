#include <iostream>
#include "linkedtree.h"
using namespace std;

int main() {
    LinkedTree tree;

    tree.addNode(1, 0, "", "Are you nervous?");
    tree.addNode(2, 1, "Yes", "Savings account");
    tree.addNode(3, 1, "No", "Need access within 5 years?");

    cout << "Leaf nodes: " << tree.getLeafCount() << endl;
    cout << "Tree height: " << tree.getHeight() << endl;

    return 0;
}