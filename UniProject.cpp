#include <iostream>
#include <string>
#include <windows.h>
#include <stdio.h>
#include <sqlite3.h>

using namespace std;

//I am passing the directory to the function using the paramater
static int createDB(const char* s);
static int createTable(const char* s);
static int insertData(const char* s);
static int selectData(const char* s);
static int returnToMain();
static int mainMenu();


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


//TODO: UPDATE AND DELETE FROM DB.
//TODO: POLISHING THE MENU
//TODO: PRINTING THE DATA TO TXT FILE


int main()
{
	//Auth();

	const char* dir = "C:\\Programming\\UniProject\\Books.db";
	sqlite3* DB;

	createDB(dir); //creating the database file
	createTable(dir); //creating the table

	mainMenu();


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
		int exit = sqlite3_open(s, &DB); //it'll take the address in memory and use it in exec() func. (0x085121 for example)

		cout << "Book's Title: \n";
		cin >> b.Title;
		cout << "Book's Author: \n";
		cin >> b.Author;
		cout << "Book's Page: \n";
		cin >> b.Page;
		cout << "Book's Category: \n";
		cin >> b.Categhory;

		//sqlite3 can catch the variable without an error whether string or int anyway so NO need to specify the page var as a integer.
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
	int _selection;
	string _input;


	exit = sqlite3_open(s, &DB);

	cout << "Options: [1]: Print All Books, [2]: Search Book by the Title, [3]: Search Book by the ID, [4]: Search Book by the Category" << endl; //literally a TODO: Right now.

	cin >> _selection;



	switch (_selection)
	{
	case 1:
		exit = sqlite3_exec(DB, "SELECT * FROM BOOKS", callbackFunc, NULL, NULL); //for all books
		returnToMain();
		break;
	case 2:
		cout << "Title: ";
		cin >> _input;
		{ //Solution of: transfer of control bypasses initialization
			string sqlTitle("SELECT * FROM BOOKS WHERE TITLE='" + _input + "'");
			exit = sqlite3_exec(DB, sqlTitle.c_str(), callbackFunc, NULL, NULL);
		}
		break;
	case 3:
		cout << "ID: ";
		cin >> _input;
		{
			string sqlTitle("SELECT * FROM BOOKS WHERE ID='" + _input + "'");
			exit = sqlite3_exec(DB, sqlTitle.c_str(), callbackFunc, NULL, NULL);
		}

		break;
	case 4:
		cout << "Category: ";
		cin >> _input;
		{
			string sqlTitle("SELECT * FROM BOOKS WHERE CATEGORY='" + _input + "'");
			exit = sqlite3_exec(DB, sqlTitle.c_str(), callbackFunc, NULL, NULL);
		}

		break;
	default:

		break;
	}




	return 0;
}

static int updateData(const char* s)
{
	sqlite3* DB;
	int exit = 0;

	exit = sqlite3_open(s, &DB);

	//exit = sqlite3_exec();
}

static int mainMenu()
{
	const char* dir = "C:\\Programming\\UniProject\\Books.db";
	//MENU VARS
	cout << "Register a Book press [1]\n Search a Book press [2]\n Delete Book from DB press [3]\n";
	int options;
	cin >> options;

	switch (options)
	{
	case 1:
		cout << "Registering Books to Database\n";
		system("CLS");
		insertData(dir);
		break;
	case 2:
		cout << "Searching in Database";
		Sleep(500);
		system("CLS");
		selectData(dir);
		break;
	case 3:
		cout << "Deleting from Database";
		break;
	}

	return 0;
}

static int returnToMain()
{
	string answer;
	cout << "Do you want to return to Main Menu? [y] yes, [n] no ";
	cin >> answer;

	if (answer == "y")
	{
		Sleep(500);
		system("CLS");
		return mainMenu();
	}
	else
	{
		exit(0);
	}
	return 0;
}