#include <iostream>
#include "linkedtree.h"
using namespace std;

int main() {
    LinkedTree tree;

// prompt for input file

string filename;

cout << "Enter the input file name (including.txt): ";
getline(cin,filename);

if (!tree.treeFileLoad(filename)) {
    cout << "Failed to load tree!" << endl;
    return 1;
}

    cout << "Output file Written as about_tree.txt" << endl;
    tree.createOutputFile();
    
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



    string input;

    while (true) {
        cout << "\nWhich node would you like to explore (enter position or \"exit\"): ";
        cin >> input;

        // Exit the program
        if (input == "exit") {
            cout << "Goodbye!" << endl;
            break;
        }

        // Make sure the input is a valid integer
        int position;

        try {
            size_t index;
            position = stoi(input, &index);

            if (index != input.length()) {
                cout << "Invalid input. Please try again." << endl;
                continue;
            }
        }
        catch (...) {
            cout << "Invalid input. Please try again." << endl;
            continue;
        }

        Node* found = tree.findNode(position);

        if (found == nullptr) {
            cout << "Invalid input. Please try again." << endl;
            continue;
        }


//node's content
        cout << "\nNode's content: " << found->content << endl;
    
// display 1 ancestor (AKA parent)
        if (found->parent != nullptr) {
            cout << "Ancestor: " << found->parent->content << endl;
        }
        else {
            cout << "Ancestor: None" << endl;
        }



// display 1 descendent (AKA first child)
        if (!found->children.empty()) {
            cout << "Descendant: " << found->children[0]->content << endl;
        }
        else {
            cout << "Descendant: None" << endl;
        }

// display 1 sibling
    Node* sibling = nullptr;

    if (found->parent != nullptr) {
        for (Node* child : found->parent->children) {
            if (child != found){
                sibling = child;
                break;
            }
        }
    }
    if (sibling != nullptr) {
        cout << "Sibling: " << sibling ->content << endl;
    }
    else {
        cout << "Sibling: None" << endl;
        }
    }


    return 0;
}