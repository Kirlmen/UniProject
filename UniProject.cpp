#include <iostream>
#include <string>
#include <windows.h>
#include <stdio.h>
#include <sqlite3.h>

using namespace std;

static int createDB(const char* s);
static int createTable(const char* s);
static int insertData(const char* s);
static int selectData(const char* s);


class Books
{
public:
    string Title;
    string Categhory;
    string Author;
    string Page;
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
        insertData(dir);
        break;
    case 2:
        cout << "searching category";
        selectData(dir);
        break;
    case 3:
        cout << "searching books";
        break;
    default:
        break;
    }

    return 0;
}


static int insertData(const char* s)
{
    Books b;
    sqlite3* DB;
    char* messageError;
    bool wantToContinue = false;
    string inputContinue;

    do
    {
        int exit = sqlite3_open(s, &DB); //it'll take the address in memory and use it in exec() func. (0x085121 for ex.)

        cout << "Book's Title: \n";
        cin >> b.Title;
        cout << "Book's Author: \n";
        cin >> b.Author;
        cout << "Book's Page: \n";
        cin >> b.Page;
        cout << "Book's Category: \n";
        cin >> b.Categhory;

        //sqlite3 can catch the variable without an error whether string or int anyway so no need to specify the page var as a integer.
        string sql("INSERT INTO BOOKS (TITLE, AUTHOR, PAGE, CATEGORY) VALUES('" + b.Title + "','" + b.Author + "','" + b.Page + "','" + b.Categhory + "'); ");


        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Error Inserting the data." << endl;
            sqlite3_free(messageError);
        }
        else
            cout << "Successfully Recorded!" << endl;

        cout << "Want to insert data again? yes [y], no [n]" << endl;
        cin >> inputContinue;
        inputContinue == "y" ? wantToContinue = true : false;
        
    } while (wantToContinue);

   
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
        "CATEGORY   CHAR(50) NOT NULL );";

    try
    {
        int exit = 0; 
        exit = sqlite3_open(s, &DB);
    
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError); //just a callback
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

static int callbackFunc(void* unused, int count, char** data, char** columns)
{
    int i;
   
    for (i = 0; i < count; i++) {
        printf("The data in column \"%s\" is: %s\n", columns[i], data[i]);
    }

    printf("\n");

    return 0;
}

static int selectData(const char* s)
{
    sqlite3* DB;
    int exit = 0;
    exit = sqlite3_open(s, &DB);
    
    cout << "Options: [1]: Print All Books, [2]: Search Book by the Name, [3]: Search Book by the ID, [4]: Search Book by the Category" << endl; //literally a TODO: Right now.
    int _selection;
    cin >> _selection;

    
    switch (_selection)
    {
    case 1:
        exit = sqlite3_exec(DB, "SELECT * FROM BOOKS", callbackFunc, NULL, NULL); //for all books
        break;
    case 2:
        break;
    case 3:
        break;
    case 4: 
        break;
    default:
        break;
    }

    

    
    return 0;
}
