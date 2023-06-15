#ifndef AVL_TREE_LIBRARY_H
#define AVL_TREE_LIBRARY_H

#include "memory"
#include "vector"
#include "algorithm"
#include "cmath"

using namespace std;

class RawComparator {
public:
    template<typename T>
    int operator() (const T& a, const T& b) {
        if (a < b) return -1;
        else if (a > b) return 1;
        else return 0;
    }
};


template<typename T>
struct Node {
    T value;
    shared_ptr<Node> left;
    shared_ptr<Node> right;
    shared_ptr<Node> parent;

    int height;

    explicit Node(T value) : value(value), left(nullptr), right(nullptr), parent(nullptr), height(1) {};
};

template<typename T, class Comparator = RawComparator>
class AVLTree {
private:
    typedef shared_ptr<Node<T>> NodePtr;
    Comparator comparator = Comparator();
    NodePtr root;
public:
    AVLTree() : root(nullptr);
    explicit AVLTree(Comparator comp) : root(nullptr), comparator(comp);
    ~AVLTree() = default;

    void insert(T value) {
        insert(root, value);
    }

    void remove(T value) {
        remove(root, value);
    }

    NodePtr search(T value) {
        return search(root, value);
    }

    bool contains(T value) {
        return contains(root, value);
    }

    vector<T> getSorted() {
        vector<T> result;
        getSorted(root, result);
        return result;
    }

    int getHeight() {
        return getHeight(root);
    }
private:
    void insert(NodePtr &node, T value) {
        if (node == nullptr) {
            node = make_shared<Node<T>>(value);
            return;
        }
        if (comparator(value, node->value)) {
            insert(node->left, value);
        } else if (comparator(node->value, value)) {
            insert(node->right, value);
        } else {
            return;
        }
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        int balance = getHeight(node->left) - getHeight(node->right);
        if (balance > 1) {
            if (getHeight(node->left->left) >= getHeight(node->left->right)) {
                rightRotate(node);
            } else {
                leftRotate(node->left);
                rightRotate(node);
            }
        } else if (balance < -1) {
            if (getHeight(node->right->right) >= getHeight(node->right->left)) {
                leftRotate(node);
            } else {
                rightRotate(node->right);
                leftRotate(node);
            }
        }
    }
    void remove(NodePtr &node, T value) {
        if (node == nullptr) {
            return;
        }
        if (comparator(value, node->value)) {
            remove(node->left, value);
        } else if (comparator(node->value, value)) {
            remove(node->right, value);
        } else {
            if (node->left == nullptr && node->right == nullptr) {
                node = nullptr;
            } else if (node->left == nullptr) {
                node = node->right;
            } else if (node->right == nullptr) {
                node = node->left;
            } else {
                NodePtr min = node->right;
                while (min->left != nullptr) {
                    min = min->left;
                }
                node->value = min->value;
                remove(node->right, min->value);
            }
        }
        if (node == nullptr) {
            return;
        }
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        int balance = getHeight(node->left) - getHeight(node->right);
        if (balance > 1) {
            if (getHeight(node->left->left) >= getHeight(node->left->right)) {
                rightRotate(node);
            } else {
                leftRotate(node->left);
                rightRotate(node);
            }
        } else if (balance < -1) {
            if (getHeight(node->right->right) >= getHeight(node->right->left)) {
                leftRotate(node);
            } else {
                rightRotate(node->right);
                leftRotate(node);
            }
        }
    }
    NodePtr search(NodePtr &node, T value) {
        if (node == nullptr) {
            return nullptr;
        }
        if (comparator(value, node->value)) {
            return search(node->left, value);
        } else if (comparator(node->value, value)) {
            return search(node->right, value);
        } else {
            return node;
        }
    }
    bool contains(NodePtr &node, T value) {
        if (node == nullptr) {
            return false;
        }
        if (comparator(value, node->value)) {
            return contains(node->left, value);
        } else if (comparator(node->value, value)) {
            return contains(node->right, value);
        } else {
            return true;
        }
    }
    void getSorted(NodePtr &node, vector<T> &result) {
        if (node == nullptr) {
            return;
        }
        getSorted(node->left, result);
        result.push_back(node->value);
        getSorted(node->right, result);
    }
    int getHeight(NodePtr &node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }
    void leftRotate(NodePtr &node) {
        NodePtr right = node->right;
        node->right = right->left;
        if (right->left != nullptr) {
            right->left->parent = node;
        }
        right->parent = node->parent;
        if (node->parent == nullptr) {
            root = right;
        } else if (node == node->parent->left) {
            node->parent->left = right;
        } else {
            node->parent->right = right;
        }
        right->left = node;
        node->parent = right;
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        right->height = max(getHeight(right->left), getHeight(right->right)) + 1;
    }
    void rightRotate(NodePtr &node) {
        NodePtr left = node->left;
        node->left = left->right;
        if (left->right != nullptr) {
            left->right->parent = node;
        }
        left->parent = node->parent;
        if (node->parent == nullptr) {
            root = left;
        } else if (node == node->parent->left) {
            node->parent->left = left;
        } else {
            node->parent->right = left;
        }
        left->right = node;
        node->parent = left;
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        left->height = max(getHeight(left->left), getHeight(left->right)) + 1;
    }
};


#endif //AVL_TREE_LIBRARY_H
