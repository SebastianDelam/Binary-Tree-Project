#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    string content;
    string edgelabel;
    Node* parent;
    vector<Node*> children;
    int position;
    int Nodelevel;
    Node(int pos, int level, string prevText, string text) {
        position = pos;
        Nodelevel = level;
        edgelabel = prevText;
        content = text;
        parent = nullptr;
    }
};

class LinkedTree {
private:
    Node* root;
    vector<Node*> path; // Keeps track of the current path through the tree

    // Deletes a node and all of its children.
    void destroyTree(Node* current) {
        if (current == nullptr) {
            return;
        }

        for (Node* child : current->children) {
            destroyTree(child);
        }
        delete current;
    }

    // Counts nodes that have no children
    int countLeaves(Node* current) {
        if (current == nullptr) {
            return 0;
        }
        if (current->children.empty()) {
            return 1;
        }

        int total = 0;
        for (Node* child : current->children) {
            total += countLeaves(child);
        }
        return total;
    }

    // Counts nodes that have at least one child
    int countInternal(Node* current) {
        if (current == nullptr || current->children.empty()) {
            return 0;
        }

        int total = 1;
        for (Node* child : current->children) {
            total += countInternal(child);
        }
        return total;
    }

    // Calculates height 
    int height(Node* current) {
        if (current == nullptr) {
            return -1;
        }

        int tallest = -1;
        for (Node* child : current->children) {
            int childHeight = height(child);
            if (childHeight > tallest) {
                tallest = childHeight;
            }
        }
        return tallest + 1;
    }

    void printTreeNodes(Node* current, ostream& output) {
        if (current == nullptr) {
            return;
        }

        // Print two dashes for each level
        for (int i = 0; i < current->Nodelevel * 2; i++) {
            output << "-";
        }

        // Print the edge label
        if (current->parent != nullptr) {
            output << "[" << current->edgelabel << "] ";
        }

        output << current->content << endl;

        // Print every child
        for (Node* child : current->children) {
            printTreeNodes(child, output);
        }
        
    }
    void printPreorderNodes(Node* current, bool leavesOnly, ostream& output) {
        if (current == nullptr) {
            return;
        }

        bool isLeaf = current->children.empty();

        if (isLeaf == leavesOnly) {
            output << current->content << endl;
        }

        for (Node* child : current->children) {
            printPreorderNodes(child, leavesOnly, output);
        }
    }
    //need to tell if a tree is binary, proper, perrfect, and balanced
    bool checkBinary(Node* current) {
        if (current == nullptr) {
            return true;
        }

        if (current->children.size() > 2) {
            return false;
        }

        for (Node* child : current->children) {
            if (!checkBinary(child)) {
                return false;
            }
        }

        return true;
        }

    bool checkProper(Node* current) {
        if (current == nullptr) {
            return true;
        }

        int childCount = current->children.size();

        if (childCount != 0 && childCount != 2) {
            return false;
        }

        for (Node* child : current->children) {
            if (!checkProper(child)) {
                return false;
            }
        }

        return true;
    }
    
    bool checkPerfect(Node* current, int depth, int treeHeight) {

        // Leaves must all be at the same depth
        if (current->children.empty()) {
            return depth == treeHeight;
        }

        // Internal nodes must have exactly 2 children
        if (current->children.size() != 2) {
            return false;
        }

        // Check both children
        for (Node* child : current->children) {
            if (!checkPerfect(child, depth + 1, treeHeight)) {
                return false;
            }
        }

        return true;
    }
    
    bool checkBalanced(Node* current) {
        if (current == nullptr) {
            return true;
        }

        // This check is for binary trees
        if (current->children.size() > 2) {
            return false;
        }

        int leftHeight = -1;
        int rightHeight = -1;

        // Get the heights of existing child subtrees
        if (current->children.size() >= 1) {
            leftHeight = height(current->children[0]);
        }

        if (current->children.size() == 2) {
            rightHeight = height(current->children[1]);
        }

        // Find the difference between heights
        int difference = leftHeight - rightHeight;

        if (difference < 0) {
            difference = -difference;
        }

        if (difference > 1) {
            return false;
        }

        // Make sure every child subtree is balanced too
        for (Node* child : current->children) {
            if (!checkBalanced(child)) {
                return false;
            }
        }

        return true;
    }

    
    Node* searchNode(Node* current, int pos) {
        if (current == nullptr) {
            return nullptr;
        }

        // Check if this is the node we're looking for
        if (current->position == pos) {
            return current;
        }

        // Search through each child
        for (Node* child : current->children) {
            Node* found = searchNode(child, pos);

            if (found != nullptr) {
                return found;
            }
        }

        // Node wasn't found
        return nullptr;
    }




public:
    LinkedTree() : root(nullptr) {}

    ~LinkedTree() {
        destroyTree(root);
    }

    // Add nodes in preorder
    void addNode(int pos, int level, string edge, string text) {
        if (root == nullptr) {
            if (level != 0) {
                cout << "Invalid root level" << endl;
                return;
            }
            root = new Node(pos, level, edge, text);
            path.push_back(root);
            return;
        }

        int pathSize = path.size();
        if (level < 1 || level > pathSize) {
            cout << "Invalid node level" << endl;
            return;
        }

        // Go back up the tree until we reach this node's parent
        while (pathSize > level) {
            path.pop_back();
            pathSize--;
        }

        Node* parentNode = path.back();
        Node* newNode = new Node(pos, level, edge, text);

        newNode->parent = parentNode;
        parentNode->children.push_back(newNode);
        path.push_back(newNode);
    }

    int getLeafCount() {
        return countLeaves(root);
    }

    int getInternalCount() {
        return countInternal(root);
    }

    int getHeight() {
        return height(root);
    }

    void printTree(ostream& output) {
        printTreeNodes(root, output);
    }

    void printPreorder(ostream& output, bool leavesOnly) {
        printPreorderNodes(root, leavesOnly, output);
    }

    bool isBinary() {
    return checkBinary(root);
    }

    bool isProper() {
        return checkProper(root);
    }
    bool isPerfect() {
        if (root == nullptr) {
            return false;
        }

        return checkPerfect(root, 0, getHeight());
    }

    bool isBalanced() {
        return checkBalanced(root);
    }

    Node* findNode(int pos) {
        return searchNode(root, pos);
    }
};
