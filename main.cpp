#include <iostream>
#include <stdexcept>

// Definición de la clase Nodo
class Node {
public:
    int key;
    Node* left;
    Node* right;
    Node* parent;

    Node(int key) : key(key), left(nullptr), right(nullptr), parent(nullptr) {}
};

// Definición de la clase MaxHeap
class MaxHeap {
private:
    Node* root;
    Node* lastInserted;

    void heapifyUp(Node* node) {
        if (node->parent && node->key > node->parent->key) {
            std::swap(node->key, node->parent->key);
            heapifyUp(node->parent);
        }
    }

    void heapifyDown(Node* node) {
        if (!node) return;

        Node* largest = node;
        if (node->left && node->left->key > largest->key) {
            largest = node->left;
        }
        if (node->right && node->right->key > largest->key) {
            largest = node->right;
        }

        if (largest != node) {
            std::swap(node->key, largest->key);
            heapifyDown(largest);
        }
    }

    Node* getLastNode() {
        if (!lastInserted) return nullptr;

        Node* node = lastInserted;
        while (node->parent && node == node->parent->right) {
            node = node->parent;
        }

        if (node->parent) {
            if (node->parent->right) {
                node = node->parent->right;
                while (node->left) {
                    node = node->left;
                }
            } else {
                node = node->parent;
            }
        } else {
            while (node->left) {
                node = node->left;
            }
        }

        return node;
    }

public:
    MaxHeap() : root(nullptr), lastInserted(nullptr) {}

    void insert(int key) {
        Node* newNode = new Node(key);
        if (!root) {
            root = newNode;
            lastInserted = newNode;
            return;
        }

        Node* parent = getLastNode();
        newNode->parent = parent;
        if (!parent->left) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        lastInserted = newNode;
        heapifyUp(newNode);
    }

    int extractMax() {
        if (!root) {
            throw std::out_of_range("Heap is empty");
        }

        int maxValue = root->key;
        if (root == lastInserted) {
            delete root;
            root = lastInserted = nullptr;
            return maxValue;
        }

        root->key = lastInserted->key;

        Node* parent = lastInserted->parent;
        if (parent->right == lastInserted) {
            delete parent->right;
            parent->right = nullptr;
        } else {
            delete parent->left;
            parent->left = nullptr;
        }

        lastInserted = getLastNode();
        heapifyDown(root);

        return maxValue;
    }

    int getMax() const {
        if (!root) {
            throw std::out_of_range("Heap is empty");
        }
        return root->key;
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    void printHeap(Node* node, int space = 0, int height = 10) const {
        if (!node || height == 0) return;

        space += 5;
        printHeap(node->right, space, height - 1);

        std::cout << std::endl;
        for (int i = 5; i < space; ++i) std::cout << ' ';
        std::cout << node->key << "\n";

        printHeap(node->left, space, height - 1);
    }

    void printHeap() const {
        printHeap(root);
    }
};

int main() {
    MaxHeap maxHeap;

    maxHeap.insert(3);
    maxHeap.insert(2);
    maxHeap.insert(15);
    maxHeap.insert(5);
    maxHeap.insert(4);
    maxHeap.insert(45);

    std::cout << "Max-Heap tree:\n";
    maxHeap.printHeap();

    std::cout << "Max value extracted: " << maxHeap.extractMax() << std::endl;
    std::cout << "Max-Heap tree after extraction:\n";
    maxHeap.printHeap();

    return 0;
}
