#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <D:\University Stuff\Abdullah University-3\DSA\Lab\Lab Work\Final Semester Project\class\Queue.cpp>
#include <D:\University Stuff\Abdullah University-3\DSA\Lab\Lab Work\Final Semester Project\class\Stack.cpp>
using namespace std;

class User
{
public:
    Stack s1;
    Queue q1;
    struct book
    {
        int book_ID;
        string book_title;
        string author_name;
        book *next;
        book *head;
        book *current;
        book(int a, string b, string c) : book_ID(a), book_title(b), author_name(c), next(nullptr) {}
    } *book_struct;

    struct UserDetails
    {
        int user_ID;
        string user_name;
        double fine_amount;
        UserDetails *next;
        string data;
        UserDetails(const string &value) : user_name(value), next(nullptr) {}
        UserDetails() {}
    } *user_detail_struct;
    bool user_cred(const string &a, const string &b, const string c[], const string d[], int size);
    void bookBorrow(int ID);
    void returnBook(int ID);
    void seeBookList(const string &filename);
    void seeMyBooks();
    void payFine(double amount);
    void saveDataToFile(const string a[], int size, const string &textFile);
    void saveDataToFile(const string a[][100], int rows, int cols, const string &textFile);
    void loadDataFromFile(string a[], int size, const string &textFile);
    void loadDataFromFile(string a[][100], int rows, int cols, const string &textFile);
    void saveDataToFile(UserDetails *head, const string &textFile);
    void loadDataFromFile(UserDetails *&head, const string &textFile);
    void saveDataToFile(book *head, const string &textFile);
    void loadDataFromFile(book *&head, const string &textFile);
    double calculateTotalFine();
    User();
};
User::User()
{
    book_struct = nullptr;
    user_detail_struct = nullptr;
}

bool User::user_cred(const string &a, const string &b, const string c[], const string d[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (a == c[i] && b == d[i])
        {
            return true;
        }
    }
    return false;
}

void User::bookBorrow(int ID)
{
    book *q, *prev;
    q = book_struct;
    prev = nullptr;

    while (q != nullptr && q->book_ID != ID)
    {
        prev = q;
        q = q->next;
    }

    if (q == nullptr)
    {
        cout << "\nThere is no Book with the ID: " << ID << endl;
        return;
    }

    // Book found, now remove it from the linked list
    if (prev == nullptr)
    {
        // Book is at the beginning of the list
        book_struct = q->next;
    }
    else
    {
        prev->next = q->next;
    }

    delete q;
    q1.enqueue(ID);
    saveDataToFile(book_struct, "borrowed_books.txt");
}

void User::returnBook(int bookID)
{
    // Check if the list is empty
    if (!book_struct)
    {
        cout << "This user has no borrowed books.\n";
        return;
    }

    // If the first node contains the book to be returned
    if (book_struct->book_ID == bookID)
    {
        book *temp = book_struct;
        book_struct = book_struct->next;
        delete temp;
        cout << "Book with ID " << bookID << " has been returned.\n";
        return;
    }

    // Traverse the list to find the book to be returned
    book *current = book_struct;
    while (current->next && current->next->book_ID != bookID)
    {
        current = current->next;
    }

    // If the book is found, remove it from the list
    if (current->next)
    {
        book *temp = current->next;
        current->next = current->next->next;
        delete temp;
        cout << "Book with ID " << bookID << " has been returned.\n";
    }
    else
    {
        // Book not found in the user's borrowed books
        cout << "Book with ID " << bookID << " is not currently borrowed by this user.\n";
    }

    Queue tempQueue;
    while (!q1.isEmpty())
    {
        int currentID = q1.peek();
        q1.dequeue();

        if (currentID != bookID)
        {
            tempQueue.enqueue(currentID);
        }
    }

    // Copy the temporary queue back to the original
    while (!tempQueue.isEmpty())
    {
        q1.enqueue(tempQueue.peek());
        tempQueue.dequeue();
    }
    saveDataToFile(book_struct, "borrowed_books.txt");
}

void User::seeBookList(const string &filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    cout << "List of available books:\n";

    string line;
    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
}
void User::seeMyBooks()
{
    cout << "Books borrowed by User " << user_detail_struct->user_ID << ":\n";

    // Check if the user has no borrowed books
    if (!book_struct)
    {
        cout << "No books borrowed.\n";
        return;
    }

    // Traverse the list and print each borrowed book
    book *current = book_struct;
    while (current)
    {
        cout << "Book ID: " << current->book_ID << "\n";
        cout << "Book Name: " << current->book_title << "\n";
        cout << "Author Title: " << current->author_name << "\n";
        current = current->next;
    }
}
void User::payFine(double amount)
{
    if (amount < 0)
    {
        cerr << "Invalid payment amount. Please provide a positive amount.\n";
        return;
    }

    if (amount > user_detail_struct->fine_amount)
    {
        cerr << "Payment amount exceeds the current fine. Please check the amount.\n";
        return;
    }

    user_detail_struct->fine_amount -= amount;

    cout << "Payment of $" << amount << " successful. Remaining fine: $" << user_detail_struct->fine_amount << "\n";
    s1.push(amount);
    saveDataToFile(book_struct, "borrowed_books.txt");
}

double User::calculateTotalFine()
{
    double totalFine = 0.0;

    // Iterate through the fine stack to calculate the total fine
    Stack tempStack = s1; // Copy the stack to not modify the original
    while (!tempStack.isEmpty())
    {
        totalFine += tempStack.peek();
        tempStack.pop();
    }

    return totalFine;
}

void User::loadDataFromFile(UserDetails *&head, const string &textFile)
{
    ifstream fileScanner(textFile);

    if (fileScanner.is_open())
    {
        string line;
        while (getline(fileScanner, line))
        {
            if (!line.empty())
            {
                UserDetails *newNode = new UserDetails(line);
                if (head == nullptr)
                {
                    head = newNode;
                }
                else
                {
                    UserDetails *current = head;
                    while (current->next != nullptr)
                    {
                        current = current->next;
                    }
                    current->next = newNode;
                }
            }
        }

        fileScanner.close();
    }
    else
    {
        cerr << "Error: File not found" << endl;
    }
}

void User ::saveDataToFile(UserDetails *head, const string &textFile)
{
    ofstream writer(textFile);

    if (writer.is_open())
    {
        UserDetails *current = head;
        while (current != nullptr)
        {
            if (!current->data.empty())
            {
                writer << current->data << '\n';
            }
            current = current->next;
        }

        writer.close();
    }
    else
    {
        cerr << "Failed to save data to file." << endl;
    }
}

void User::loadDataFromFile(book *&head, const string &textFile)
{
    ifstream fileScanner(textFile);

    if (fileScanner.is_open())
    {
        string line, a;
        int b;

        while (getline(fileScanner, line))
        {
            if (!line.empty())
            {
                book *newNode = new book(b, line, a);
                if (head == nullptr)
                {
                    head = newNode;
                }
                else
                {
                    book *current = head;
                    while (current->next != nullptr)
                    {
                        current = current->next;
                    }
                    current->next = newNode;
                }
            }
        }

        fileScanner.close();
    }
    else
    {
        cerr << "Error: File not found" << endl;
    }
}

void User::saveDataToFile(book *head, const string &textFile)
{
    ofstream writer(textFile);

    if (writer.is_open())
    {
        book *current = head;
        while (current != nullptr)
        {
            writer << current->book_ID << '\n';
            writer << current->book_title << '\n';
            writer << current->author_name << '\n';

            current = current->next;
        }
        writer.close();
    }
    else
    {
        cerr << "Failed to save data to file." << endl;
    }
}

void User::saveDataToFile(const string a[], int size, const string &textFile)
{
    ofstream writer(textFile);

    if (writer.is_open())
    {
        for (int i = 0; i < size; i++)
        {
            if (!a[i].empty())
            {
                writer << a[i] << '\n';
            }
        }

        writer.close();
    }
    else
    {
        cerr << "Failed to save data to file." << endl;
    }
}

void User::saveDataToFile(const string a[][100], int rows, int cols, const string &textFile)
{
    ofstream writer(textFile);

    if (writer.is_open())
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (!a[i][j].empty())
                {
                    writer << a[i][j] << '\n';
                }
            }
        }

        writer.close();
    }
    else
    {
        cerr << "Failed to save data to file." << endl;
    }
}

void User::loadDataFromFile(string a[], int size, const string &textFile)
{
    ifstream fileScanner(textFile);

    if (fileScanner.is_open())
    {
        int index = 0;
        while (fileScanner.good() && index < size)
        {
            getline(fileScanner, a[index]);
            index++;
        }

        fileScanner.close();
    }
    else
    {
        cerr << "Error: File not found" << endl;
    }
}

void User::loadDataFromFile(string a[][100], int rows, int cols, const string &textFile)
{
    ifstream fileScanner(textFile);

    if (fileScanner.is_open())
    {
        int index = 0;
        while (fileScanner.good())
        {
            string line;
            getline(fileScanner, line);

            if (index < rows)
            {
                istringstream iss(line);
                int j = 0;
                while (j < cols && iss >> a[index][j])
                {
                    j++;
                }
            }

            index++;
        }

        fileScanner.close();
    }
    else
    {
        cerr << "Error: File not found" << endl;
    }
}