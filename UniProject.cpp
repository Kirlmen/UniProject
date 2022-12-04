#include <iostream>
#include <string>
#include <windows.h>
#include <stdio.h>
#include <sqlite3.h>

using namespace std;

static int createDB(const char* s);
static int createTable(const char* s);

class Books
{
public:
    int ID;
    string Title;
    string Categhory;
    string Author;
    int Page;
    string Date;
};

void Auth()
{
    string name;
    string password;
    bool canEnter = false;
    while (true)
    {
        cout << "Enter the name: " << endl;
        cin >> name;
        cout << "Enter the password: " << endl;
        cin >> password;

        if (name == "admin" && password == "admin")
        {
            system("CLS");
            cout << "Success!" << endl;
            Sleep(500);
            canEnter = true;
            break;
        }
        else {
            canEnter = false;
            system("CLS");
            cout << "Access Denied!" << endl;
            Sleep(500);

        }
    }
}

void RegisterBook()
{
    Books b;

    
}





int main(int argc, char const* argv[])
{
    //Auth();
    
    const char* dir = "C:\\Programming\\UniProject\\Books.db";
    sqlite3* DB;

    createDB(dir); //creating the database
    createTable(dir); //creating the table




    //MENU VARS
    cout << "Register a book press [1]\nSearch a category press [2]\nSearch for Books press [3]\n";
    int options;
    cin >> options;

    switch (options)
    {
    case 1:
        cout << "registering books\n";
        RegisterBook();
        break;
    case 2:
        cout << "searching category";
        break;
    case 3:
        cout << "searching books";
        break;
    default:
        break;
    }

    return 0;
}


static int createDB(const char* s)
{
    sqlite3* DB;
    int exit = 0;
    exit = sqlite3_open(s, &DB); //if it's not exist, it'll create.

    sqlite3_close(DB);

    return 0;
}

static int createTable(const char* s)
{
    sqlite3* DB;
    char* messageError;

    string sql = "CREATE TABLE IF NOT EXISTS BOOKS("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "TITLE      TEXT NOT NULL, "
        "AUTHOR    TEXT NOT NULL, "
        "PAGE       INT, "
        "CATEGORY   CHAR(50) NOT NULL);";

    try
    {
        int exit = 0;
        exit = sqlite3_open(s, &DB);
        /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Error in createTable function." << endl;
            sqlite3_free(messageError);
        }
        else
            cout << "Table created Successfully" << endl;
        sqlite3_close(DB);
    }
    catch (const exception& e)
    {
        cerr << e.what();
    }

    return 0;
}
