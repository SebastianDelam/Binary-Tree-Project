#include <iostream>
#include "linkedtree.h"
using namespace std;

int main() {
    LinkedTree tree;

    tree.addNode(1, 0, "", "Are you nervous?");
    tree.addNode(2, 1, "Yes", "Savings account");
    tree.addNode(3, 1, "No", "Need access within 5 years?");
    tree.addNode(4, 2, "Yes", "Money market fund");
    tree.addNode(5, 2, "No", "Willing to accept risks?");
    tree.addNode(6, 3, "Yes", "Stock portfolio");
    tree.addNode(7, 3, "No", "Diversified portfolio");

    cout << "Leaf nodes: " << tree.getLeafCount() << endl;
    cout << "Tree height: " << tree.getHeight() << endl;
    cout << "Internal nodes: " << tree.getInternalCount() << endl;


    cout << "\nTree:\n";
    tree.printTree(cout);

    cout << "\nInternal nodes:\n";
    tree.printPreorder(cout, false);

    cout << "\nLeaf nodes:\n";
    tree.printPreorder(cout, true);

    cout << "\nBinary Tree: " << (tree.isBinary() ? "Yes" : "No") << endl;

    if (tree.isBinary()) {
        cout << "Proper Tree: " << (tree.isProper() ? "Yes" : "No") << endl;
    }

    if (tree.isPerfect()) {
    cout << "Perfect Tree: Yes" << endl;
    }

    else {
        cout << "Perfect Tree: No" << endl;
    }

    if (tree.isBalanced()) {
        cout << "Balanced Tree: Yes" << endl;
    }

    else {
        cout << "Balanced Tree: No" << endl;
    }

    Node* found = tree.findNode(5);

    if (found != nullptr) {
        cout << "\nFound: " << found->content << endl;

        if (found->parent != nullptr) {
            cout << "Parent: " << found->parent->content << endl;
        }
    }
    else {
        cout << "Node not found" << endl;
    }

    return 0;
}