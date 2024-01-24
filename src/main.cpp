#include <iostream>
#include <string>
#include "D:\University Stuff\Abdullah University-3\DSA\Lab\Lab Work\Final Semester Project\class\Admin.cpp"
#include "D:\University Stuff\Abdullah University-3\DSA\Lab\Lab Work\Final Semester Project\class\User.cpp"
using namespace std;

// Function to handle user panel
void userPanel(User &u1, const string usernames[], const string passwords[], int size)
{
    int UserID, BookID;
    double fine_amount;
    cout << "User\n";
    string user_name, pass_word;
    cout << "Enter your username: ";
    cin >> user_name;
    cout << "Enter your password: ";
    cin >> pass_word;

    bool check_cred_user = u1.user_cred(user_name, pass_word, usernames, passwords, size);

    if (check_cred_user)
    {
        int choice_user;
        do
        {
            cout << "\n-----------------------------------------------------------\n";
            cout << "1. Borrow a Book\n";
            cout << "-----------------------------------------------------------\n";
            cout << "2. Return a Book\n";
            cout << "-----------------------------------------------------------\n";
            cout << "3. See Available Books\n";
            cout << "-----------------------------------------------------------\n";
            cout << "4. See My Borrowed Books\n";
            cout << "-----------------------------------------------------------\n";
            cout << "5. Pay Fine\n";
            cout << "-----------------------------------------------------------\n";
            cout << "6. Log out\n";
            cout << "-----------------------------------------------------------\n";
            cout << "Enter your choice: ";
            cin >> choice_user;

            switch (choice_user)
            {
            // Implement the logic for each case
            case 1:
                cout << "Borrow a Book:\n";
                cout << "Enter the Book ID:\n";
                cin >> BookID;
                u1.bookBorrow(BookID);
                break;
            case 2:
                cout << "Return a Book:\n";
                cout << "Enter The BookID:\n";
                cin >> BookID;
                u1.returnBook(BookID);
                break;
            case 3:
                cout << "See Available Books:\n";
                cout << "Here are the available books:\n";
                u1.seeBookList("D:\\University Stuff\\Abdullah University-3\\DSA\\Lab\\Lab Work\\Final Semester Project\\db\\Books.txt");
                break;
            case 4:
                cout << "See My Borrowed Books:\n";
                cout << "Here are your books you borrowed:\n";
                u1.seeMyBooks();
                break;
            case 5:
                cout << "Pay Fine:\n";
                cout << "Enter Amount you want to pay:\n";
                cin >> fine_amount;
                u1.payFine(fine_amount);
                break;
            case 6:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Input Error. Please enter a valid choice.\n";
            }

        } while (choice_user != 6);
    }
    else
    {
        cout << "User Not Granted\n";
    }
}

// Function to handle admin panel
void adminPanel(Admin &a1, const string usernames[], const string passwords[], int size)
{
    string UserID, BookID;
    string title, a_name, u_name, date;
    bool flag;
    double challan_amount;
    cout << "Admin\n";
    string user_name, pass_word;
    cout << "Enter your username: ";
    cin >> user_name;
    cout << "Enter your password: ";
    cin >> pass_word;

    bool check_admin_cred = a1.admin_cred(user_name, pass_word, usernames, passwords, size);

    if (check_admin_cred)
    {
        cout << "Admin Granted";
        int choice_user;
        do
        {
            cout << "\n-----------------------------------------------------------\n";
            cout << "1. Add a Book\n";
            cout << "-----------------------------------------------------------\n";
            cout << "2. Add a User\n";
            cout << "-----------------------------------------------------------\n";
            cout << "3. Manage Transactions\n";
            cout << "-----------------------------------------------------------\n";
            cout << "4. Apply Challan\n";
            cout << "-----------------------------------------------------------\n";
            cout << "5. See Users\n";
            cout << "-----------------------------------------------------------\n";
            cout << "6. See Books\n";
            cout << "-----------------------------------------------------------\n";
            cout << "7. Remove a Book\n";
            cout << "-----------------------------------------------------------\n";
            cout << "8. See Transactions\n";
            cout << "-----------------------------------------------------------\n";
            cout << "9. Log out\n";
            cout << "-----------------------------------------------------------\n";
            cout << "Enter your choice: ";
            cin >> choice_user;

            switch (choice_user)
            {
            // Implement the logic for each case
            case 1:
                cout << "Add a Book:\n";
                cout << "Enter Book ID:\n";
                cin >> BookID;
                cout << "Enter Book title:\n";
                cin >> title;
                cout << "Enter Author name:\n";
                cin >> a_name;
                a1.addBook(BookID, title, a_name);
                break;
            case 2:
                cout << "Add a User:\n";
                cout << "Enter User Name: \n";
                cin >> u_name;
                cout << "Enter User ID:\n";
                cin >> UserID;
                a1.addUser(UserID, u_name);
                break;
            case 3:
                cout << "Manage Transactions:\n";
                cout << "Enter User ID:\n";
                cin >> UserID;
                cout << "Enter Book ID:\n";
                cin >> BookID;
                cout << "Enter Date in format {DD/MM/YYYY}:\n";
                cin >> date;
                cout << "The book is being borrowed by " << UserID << " Or returned for borrowing write true or for returning write false:\n";
                cin >> flag;
                a1.addTransaction(UserID, BookID, date, flag);
                break;
            case 4:
                cout << "Apply Challan:\n";
                cout << "Enter User ID:\n";
                cin >> UserID;
                cout << "Enter amount to challan:\n";
                cin >> challan_amount;
                a1.applyChallan(UserID, challan_amount);
                break;
            case 5:
                cout << "See Users:\n";
                a1.seeUsers();
                break;

            case 6:
                cout << "See Books:\n";
                a1.seeBooks();
                break;
            case 7:
                cout << "Remove a Book:\n";
                cout << "Enter Book ID:\n";
                cin >> BookID;
                a1.removeBook(BookID, "Books.txt");
                break;
            case 8:
                cout << "See Transactions:\n";
                a1.seeTransactions();
                break;
            case 9:
                cout << "Logging out...\n";
                break;
            }

        } while (choice_user != 9);
    }
    else
    {
        cout << "Admin Not Granted";
    }
}

int main(int argc, char const *argv[])
{
    Admin a1;
    User u1;
    int person_choice = 0;
    const int size = 10;
    string usernames[size];
    a1.loadDataFromFile(usernames, size, "D:\\University Stuff\\Abdullah University-3\\DSA\\Lab\\Lab Work\\Final Semester Project\\db\\UsernamesUser.txt");
    string passwords[size];
    a1.loadDataFromFile(passwords, size, "D:\\University Stuff\\Abdullah University-3\\DSA\\Lab\\Lab Work\\Final Semester Project\\db\\PasswordsUser.txt");
    string fine[size];
    a1.loadDataFromFile(fine, size, "D:\\University Stuff\\Abdullah University-3\\DSA\\Lab\\Lab Work\\Final Semester Project\\db\\FineUser.txt");
    cout << "Do you want to login as User or Admin? For User, enter 1, and for Admin, enter 2: " << endl;
    cin >> person_choice;
    switch (person_choice)
    {
    case 1:
        userPanel(u1, usernames, passwords, size);
        break;
    case 2:
        adminPanel(a1, usernames, passwords, size);
        break;
    default:
        cout << "Invalid choice\n";
        break;
    }

    return 0;
}
