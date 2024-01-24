#include <iostream>
#include <stdexcept>

class Queue
{
private:
    struct Node
    {
        int data;
        Node *next;

        Node(int value) : data(value), next(nullptr) {}
    };

    Node *front;
    Node *rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    ~Queue()
    {
        while (!isEmpty())
        {
            dequeue();
        }
    }

    bool isEmpty() const
    {
        return front == nullptr;
    }

    void enqueue(int value)
    {
        Node *newNode = new Node(value);
        if (isEmpty())
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue()
    {
        if (isEmpty())
        {
            throw std::runtime_error("Queue underflow");
        }

        Node *temp = front;
        front = front->next;
        delete temp;

        if (front == nullptr)
        {
            rear = nullptr;
        }
    }

    int peek() const
    {
        if (isEmpty())
        {
            throw std::runtime_error("Queue is empty");
        }

        return front->data;
    }
};
