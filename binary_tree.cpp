#include <iostream>
#include <queue>

template <typename T>
class BinaryTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        
        Node(T value) : data(value), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    
    // Helper function for destructor
    void destroyTree(Node* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
    
    // Helper function for insert
    Node* insertRecursive(Node* node, T value) {
        if (node == nullptr) {
            return new Node(value);
        }
        
        if (value < node->data) {
            node->left = insertRecursive(node->left, value);
        } else if (value > node->data) {
            node->right = insertRecursive(node->right, value);
        }
        
        return node;
    }
    
    // Helper function for search
    bool searchRecursive(Node* node, T value) const {
        if (node == nullptr) {
            return false;
        }
        
        if (node->data == value) {
            return true;
        }
        
        if (value < node->data) {
            return searchRecursive(node->left, value);
        }
        return searchRecursive(node->right, value);
    }
    
    // Helper function to find minimum value node
    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    
    // Helper function for delete
    Node* deleteRecursive(Node* node, T value) {
        if (node == nullptr) {
            return nullptr;
        }
        
        // Find the node to delete
        if (value < node->data) {
            node->left = deleteRecursive(node->left, value);
        }
        else if (value > node->data) {
            node->right = deleteRecursive(node->right, value);
        }
        else {
            // Case 1: Leaf node
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            // Case 2: Node with one child
            else if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // Case 3: Node with two children
            else {
                // Find inorder successor (smallest value in right subtree)
                Node* temp = findMin(node->right);
                node->data = temp->data;
                node->right = deleteRecursive(node->right, temp->data);
            }
        }
        return node;
    }
    
    // Helper functions for traversals
    void inorderTraversal(Node* node) const {
        if (node) {
            inorderTraversal(node->left);
            std::cout << node->data << " ";
            inorderTraversal(node->right);
        }
    }
    
    void preorderTraversal(Node* node) const {
        if (node) {
            std::cout << node->data << " ";
            preorderTraversal(node->left);
            preorderTraversal(node->right);
        }
    }
    
    void postorderTraversal(Node* node) const {
        if (node) {
            postorderTraversal(node->left);
            postorderTraversal(node->right);
            std::cout << node->data << " ";
        }
    }

public:
    BinaryTree() : root(nullptr) {}
    
    ~BinaryTree() {
        destroyTree(root);
    }
    
    void insert(T value) {
        root = insertRecursive(root, value);
    }
    
    bool search(T value) const {
        return searchRecursive(root, value);
    }
    
    void remove(T value) {
        root = deleteRecursive(root, value);
    }
    
    void inorder() const {
        inorderTraversal(root);
        std::cout << std::endl;
    }
    
    void preorder() const {
        preorderTraversal(root);
        std::cout << std::endl;
    }
    
    void postorder() const {
        postorderTraversal(root);
        std::cout << std::endl;
    }
    
    void levelOrder() const {
        if (!root) return;
        
        std::queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            
            std::cout << current->data << " ";
            
            if (current->left) {
                q.push(current->left);
            }
            if (current->right) {
                q.push(current->right);
            }
        }
        std::cout << std::endl;
    }
};

int main() {
    // Create a binary tree of integers
    BinaryTree<int> tree;
    
    // Insert elements
    std::cout << "Inserting elements into the tree: 50, 30, 70, 20, 40, 60, 80" << std::endl;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    
    // Display the tree using different traversal methods
    std::cout << "\nInorder traversal: ";
    tree.inorder();  // Expected: 20 30 40 50 60 70 80
    
    std::cout << "Preorder traversal: ";
    tree.preorder();  // Expected: 50 30 20 40 70 60 80
    
    std::cout << "Postorder traversal: ";
    tree.postorder();  // Expected: 20 40 30 60 80 70 50
    
    std::cout << "Level order traversal: ";
    tree.levelOrder();  // Expected: 50 30 70 20 40 60 80
   
    


    
   
    
    return 0;
}