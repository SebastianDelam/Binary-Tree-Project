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
};
