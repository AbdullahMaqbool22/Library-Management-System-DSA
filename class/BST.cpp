#include <iostream>
#include <stdexcept>

class BST
{
private:
    struct Node
    {
        int data;
        Node *left;
        Node *right;

        Node(int value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node *root;

    void insert(Node *&current, int value)
    {
        if (current == nullptr)
        {
            current = new Node(value);
        }
        else if (value < current->data)
        {
            insert(current->left, value);
        }
        else if (value > current->data)
        {
            insert(current->right, value);
        }
        // Note: If value is equal to current->data, you can handle it based on your specific requirements.
    }

    bool search(Node *current, int value) const
    {
        if (current == nullptr)
        {
            return false;
        }
        else if (value == current->data)
        {
            return true;
        }
        else if (value < current->data)
        {
            return search(current->left, value);
        }
        else
        {
            return search(current->right, value);
        }
    }

    void destroyTree(Node *&current)
    {
        if (current != nullptr)
        {
            destroyTree(current->left);
            destroyTree(current->right);
            delete current;
            current = nullptr;
        }
    }

public:
    BST() : root(nullptr) {}

    ~BST()
    {
        destroyTree(root);
    }

    void insert(int value)
    {
        insert(root, value);
    }

    bool search(int value) const
    {
        return search(root, value);
    }
};
