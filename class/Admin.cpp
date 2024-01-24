#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <D:\University Stuff\Abdullah University-3\DSA\Lab\Lab Work\Final Semester Project\class\BST.cpp>
using namespace std;

class Admin
{
public:
    BST adminUserIDsBST;
    struct Book
    {
        string book_ID;
        string book_title;
        string author_name;
        Book *next;

        Book()
        {
        }

        Book(string id, const string &name, const string &author)
            : book_ID(id), book_title(name), author_name(author) {}
    } *book_struct;

    struct BookStatus
    {
        string bookID;
        string bookName;
        string bookAuthor;
        bool bookBorrowed;
        string date;
        BookStatus *next;
        BookStatus *current;

        BookStatus(string id, const string &name, const string &author, bool borrowed, const string &d)
            : bookID(id), bookName(name), bookAuthor(author), bookBorrowed(borrowed), date(d) {}
    } *book_status_struct;

    struct User
    {
        string user_ID;
        string user_name;
        User *next;
        double fine;
        User(const string &value) : user_name(value), next(nullptr) {}
        User() {}
    } *user_struct;

    struct Transaction
    {
        string userID;
        string bookID;
        string date;
        bool isBorrowing;
        Transaction *next;
        Transaction *head;
        Transaction()
        {
        }
        Transaction(string uID, string bID, const string &dt, bool borrowing)
            : userID(uID), bookID(bID), date(dt), isBorrowing(borrowing), next(nullptr) {}
    } *transactionHistory;

    Admin();
    ~Admin();

    bool admin_cred(const string &a, const string &b, const string c[], const string d[], int size);

    void addBook(string bookID, const string &title, const string &author);
    void addUser(string userID, const string &username);
    void manageTransactions(string userID, string bookID, const string &date, bool isBorrowing);
    void applyChallan(string userID, double amount);
    void seeUsers();
    void addTransaction(const std::string &uID, const std::string &bID, const std::string &dt, bool borrowing);
    void seeBooks();
    void removeBook(const string &bookID, const string &bookFile);
    void seeTransactions();

    void saveDataToFile(const string a[], int size, const string &textFile);
    void saveDataToFile(const string a[][100], int rows, int cols, const string &textFile);
    void saveNodeDataToFile(User *head, const string &textFile);
    void saveNodeDataToFile(Transaction *head, const string &textFile);

    void loadDataFromFile(string a[], int size, const string &textFile);
    void loadDataFromFile(string a[][100], int rows, int cols, const string &textFile);
    void loadNodeDataFromFile(User *&head, const string &textFile);
    void loadNodeDataFromFile(Transaction *&head, const string &textFile);

    string val_return(const string &a, const string c[], const string b[], int size);

    void arrayToBookStatus(BookStatus *&head, string arr[], int size);
    void bookStatusToArray(BookStatus *head, string arr[], int size);
    void addBookStatus(string bookID, const string &bookName, const string &bookAuthor, bool bookBorrowed, const string &date);
    void saveNodeDataToFile(Book *head, const string &textFile);
    void loadNodeDataFromFile(Book *&head, const string &textFile);
};

Admin::Admin()
{
    book_struct = nullptr;
    user_struct = nullptr;
}

Admin::~Admin()
{
    delete book_struct;
    delete user_struct;
}

bool Admin::admin_cred(const string &a, const string &b, const string c[], const string d[], int size)
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

void Admin::addBook(string bookID, const string &title, const string &author)
{
    Book *q, *t;
    q = book_struct;
    if (q == nullptr)
    {
        book_struct = new Book;
        book_struct->book_ID = bookID;
        book_struct->book_title = title;
        book_struct->author_name = author;
        book_struct->next = nullptr;
    }
    else
    {
        q = book_struct;
        while (q->next != nullptr)
        {
            q = q->next;
        }
        t = new Book;
        t->book_ID = bookID;
        t->book_title = title;
        t->author_name = author;
        t->next = nullptr;
        q->next = t;
    }
    saveNodeDataToFile(book_struct, "D:\\University Stuff\\Abdullah University-3\\DSA\\Lab\\Lab Work\\Final Semester Project\\db\\Books.txt");
}

void Admin::addUser(string userID, const string &username)
{
    // Check if the user ID already exists in the BST
    if (adminUserIDsBST.search(stoi(userID))) // Assuming userID is an integer
    {
        cerr << "User with ID " << userID << " already exists.\n";
        return;
    }

    // Insert the new user ID into the BST
    adminUserIDsBST.insert(stoi(userID));

    User *q, *t;
    q = user_struct;
    if (q == nullptr)
    {
        user_struct = new User;
        user_struct->user_name = username;
        user_struct->user_ID = userID;
        user_struct->next = nullptr;
    }
    else
    {
        q = user_struct;
        while (q->next != nullptr)
        {
            q = q->next;
        }
        t = new User;
        t->user_ID = userID;
        t->user_name = username;
        t->next = nullptr;
        q->next = t;
    }
    saveNodeDataToFile(user_struct, "D:\\University Stuff\\Abdullah University-3\\DSA\\Lab\\Lab Work\\Final Semester Project\\db\\UsersAll.txt");
}

void Admin::manageTransactions(string userID, string bookID, const string &date, bool isBorrowing)
{
    Transaction *transaction = new Transaction(userID, bookID, date, isBorrowing);
    transaction->next = transactionHistory;
    transactionHistory = transaction;

    // Implement additional logic here based on borrowing or returning
    if (isBorrowing)
    {
        std::cout << "User " << userID << " borrowed book " << bookID << " on " << date << std::endl;
        // Implement logic to update book status, user records, etc.
    }
    else
    {
        std::cout << "User " << userID << " returned book " << bookID << " on " << date << std::endl;
        // Implement logic to update book status, user records, etc.
    }

    saveNodeDataToFile(transactionHistory, "D:\\University Stuff\\Abdullah University-3\\DSA\\Lab\\Lab Work\\Final Semester Project\\db\\transaction_history.txt");
}

void Admin::addTransaction(const std::string &uID, const std::string &bID, const std::string &dt, bool borrowing)
{
    Transaction *newTransaction = transactionHistory;
    transactionHistory->userID = uID;
    transactionHistory->bookID = bID;
    transactionHistory->date = dt;
    transactionHistory->isBorrowing = borrowing;
    newTransaction->next = transactionHistory;
    transactionHistory = newTransaction;
    saveNodeDataToFile(newTransaction, "D:\\University Stuff\\Abdullah University-3\\DSA\\Lab\\Lab Work\\Final Semester Project\\db\\transaction_history.txt");
}

void Admin::applyChallan(string userID, double amount)
{
    loadNodeDataFromFile(user_struct, "D:\\University Stuff\\Abdullah University-3\\DSA\\Lab\\Lab Work\\Final Semester Project\\db\\FineUser.txt");
    User *q = user_struct;
    while (q != nullptr)
    {
        if (userID == q->user_ID)
        {
            q->fine += amount;
            break;
        }
        q = q->next;
    }
    saveNodeDataToFile(user_struct, "D:\\University Stuff\\Abdullah University-3\\DSA\\Lab\\Lab Work\\Final Semester Project\\db\\FineUser.txt");
}

void Admin::seeUsers()
{
    User *q;
    q = user_struct;
    if (q == NULL)
    {
        cout << " \nNo data is in the list..";
        return;
    }
    cout << "\nThe items present in the list are :";
    while (q != NULL)
    {
        cout << " " << q->user_ID << " " << q->user_name;
        q = q->next;
    }
    cout << endl;
}

void Admin::seeBooks()
{
    loadNodeDataFromFile(book_struct, "D:\\University Stuff\\Abdullah University-3\\DSA\\Lab\\Lab Work\\Final Semester Project\\db\\Books.txt");
    Book *q;
    q = book_struct;
    if (q == NULL)
    {
        cout << " \nNo data is in the list..";
        return;
    }
    cout << "\nThe items present in the list are :";
    while (q != NULL)
    {
        cout << " " << q->book_ID << " " << q->book_title;
        q = q->next;
    }
    cout << endl;
    saveNodeDataToFile(book_struct, "D:\\University Stuff\\Abdullah University-3\\DSA\\Lab\\Lab Work\\Final Semester Project\\db\\Books.txt");
}

void Admin::removeBook(const string &bookID, const string &bookFile)
{
    // Load existing book data from the file
    loadNodeDataFromFile(book_struct, "D:\\University Stuff\\Abdullah University-3\\DSA\\Lab\\Lab Work\\Final Semester Project\\db\\Books.txt");

    Book *q, *r;
    q = book_struct;
    if (q == nullptr)
    {
        cerr << "No books available." << endl;
        return;
    }

    // Check if the first book needs to be removed
    if (q->book_ID == bookID)
    {
        book_struct = q->next;
        delete q;
        cout << "Book removed successfully." << endl;
        // Save the updated data structure back to the file
        saveNodeDataToFile(book_struct, "D:\\University Stuff\\Abdullah University-3\\DSA\\Lab\\Lab Work\\Final Semester Project\\db\\Books.txt");
        return;
    }

    r = q;
    while (q != nullptr)
    {
        if (q->book_ID == bookID)
        {
            r->next = q->next;
            delete q;
            cout << "Book removed successfully." << endl;
            // Save the updated data structure back to the file
            saveNodeDataToFile(book_struct, "D:\\University Stuff\\Abdullah University-3\\DSA\\Lab\\Lab Work\\Final Semester Project\\db\\Books.txt");
            return;
        }
        r = q;
        q = q->next;
    }

    cerr << "Book with ID " << bookID << " not found." << endl;
}

void Admin::seeTransactions()
{
    if (transactionHistory == nullptr)
    {
        cout << "No transactions available." << endl;
        return;
    }

    cout << "Transaction History:" << endl;
    Transaction *current = transactionHistory;

    while (current != nullptr)
    {
        cout << "User ID: " << current->userID << ", ";
        cout << "Book ID: " << current->bookID << ", ";
        cout << "Date: " << current->date << ", ";
        cout << (current->isBorrowing ? "Borrowed" : "Returned") << endl;

        current = current->next;
    }
}

void Admin::saveDataToFile(const string a[], int size, const string &textFile)
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

void Admin::saveDataToFile(const string a[][100], int rows, int cols, const string &textFile)
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

void Admin::loadDataFromFile(string a[], int size, const string &textFile)
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

void Admin::loadDataFromFile(string a[][100], int rows, int cols, const string &textFile)
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

void Admin::saveNodeDataToFile(User *head, const string &textFile)
{
    ofstream writer(textFile);

    if (writer.is_open())
    {
        User *current = head;
        while (current != nullptr)
        {
            if (!current->user_name.empty())
            {
                writer << current->user_name << '\n';
                writer << current->user_ID << '\n';
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

void Admin::loadNodeDataFromFile(User *&head, const string &textFile)
{
    ifstream fileScanner(textFile);

    if (fileScanner.is_open())
    {
        string line;
        while (getline(fileScanner, line))
        {
            if (!line.empty())
            {
                User *newNode = new User(line);
                if (head == nullptr)
                {
                    head = newNode;
                }
                else
                {
                    User *current = head;
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
void Admin::saveNodeDataToFile(Transaction *head, const std::string &textFile)
{
    std::ofstream writer(textFile);

    if (writer.is_open())
    {
        Transaction *current = head;
        while (current != nullptr)
        {
            if (!current->bookID.empty())
            {
                std::cout << "Saving data: " << current->userID << ", " << current->bookID << ", " << current->date << std::endl;
                writer << current->userID << '\n';
                writer << current->bookID << '\n';
                writer << current->date << '\n';
                writer << (current->isBorrowing ? "Borrowed" : "Returned") << '\n';
            }
            current = current->next;
        }

        std::cout << "Data saved to file." << std::endl;
        writer.close();
    }
    else
    {
        std::cerr << "Failed to open file for writing." << std::endl;
    }
}

void Admin::loadNodeDataFromFile(Transaction *&head, const string &textFile)
{
    ifstream fileScanner(textFile);

    if (fileScanner.is_open())
    {
        string line, aline, bline;
        bool a;
        while (getline(fileScanner, line))
        {
            if (!line.empty())
            {
                Transaction *newNode = new Transaction(line, aline, bline, a);
                if (head == nullptr)
                {
                    head = newNode;
                }
                else
                {
                    Transaction *current = head;
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

void Admin::saveNodeDataToFile(Book *head, const string &textFile)
{
    ofstream writer(textFile);

    if (writer.is_open())
    {
        Book *current = head;
        while (current != nullptr)
        {
            if (!current->book_title.empty())
            {
                writer << current->book_title << '\n';
                writer << current->book_ID << '\n';
                writer << current->author_name << '\n';
            }
            current = current->next;
        }

        writer.close();
    }
    else
    {
        cerr << "Failed to open file for writing." << endl;
    }
}

void Admin::loadNodeDataFromFile(Book *&head, const string &textFile)
{
    ifstream fileScanner(textFile);

    if (fileScanner.is_open())
    {
        string line, aline, bline;
        bool a;
        while (getline(fileScanner, line))
        {
            if (!line.empty())
            {
                Book *newNode = new Book(line, aline, bline);
                if (head == nullptr)
                {
                    head = newNode;
                }
                else
                {
                    Book *current = head;
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

string Admin::val_return(const string &a, const string c[], const string b[], int size)
{
    string temp = "";

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (c[i] != "" && c[i] == a)
            {
                if (i == j)
                {
                    temp = b[j];
                }
            }
        }
    }

    return temp;
}

void Admin::addBookStatus(string bookID, const string &bookName, const string &bookAuthor, bool bookBorrowed, const string &date)
{
    BookStatus *q, *t;
    q = book_status_struct;
    if (q == nullptr)
    {
        book_status_struct = new BookStatus(bookID, bookName, bookAuthor, bookBorrowed, date);
        book_status_struct->next = nullptr;
    }
    else
    {
        q = book_status_struct;
        while (q->next != nullptr)
        {
            q = q->next;
        }
        t = new BookStatus(bookID, bookName, bookAuthor, bookBorrowed, date);
        t->next = nullptr;
        q->next = t;
    }
}