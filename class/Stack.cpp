#include <iostream>
#include <stdexcept>

class Stack
{
public:
    struct Node
    {
        int data;
        Node *next;

        Node(int value) : data(value), next(nullptr) {}
    };

    Node *top;
    Stack() : top(nullptr) {}

    ~Stack()
    {
        while (!isEmpty())
        {
            pop();
        }
    }

    bool isEmpty() const
    {
        return top == nullptr;
    }

    void push(int value)
    {
        Node *newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    void pop()
    {
        if (isEmpty())
        {
            throw std::runtime_error("Stack underflow");
        }

        Node *temp = top;
        top = top->next;
        delete temp;
    }

    int peek() const
    {
        if (isEmpty())
        {
            throw std::runtime_error("Stack is empty");
        }

        return top->data;
    }
};
