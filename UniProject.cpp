#include <iostream>
#include <string>
#include <windows.h>
#include <stdio.h>
#include <sqlite3.h>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <cstdlib>

using namespace std;

//I am passing the directory to the function using the paramater
static int createDB(const char* s);
static int createTable(const char* s);
static int insertData(const char* s);
static int selectData(const char* s);
static int returnToMain();
static int mainMenu();
static int deleteData(const char* s);


class Books
{
public:
	string Title;
	string Category;
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
		system("Color 0A");
		cout << setw(60) << "Enter the name: ";
		cin >> name;
		system("Color 0A");
		cout << setw(60) << "Enter the password: ";
		cin >> password;

		if (name == "admin" && password == "admin")
		{
			system("CLS");
			cout << setw(60) << "Success!" << endl;
			Sleep(500);
			system("CLS");
			canEnter = true;
			cout << R"(
						    .-""-.
						   / .--. \
						  / /    \ \
						  | |    | |
						  | |.-""-.|
						 ///`.::::.`\
						||| ::/  \:: ;
						||; ::\__/:: ;
						 \\\ '::::' /
						  `=':-..-'`
)";
			Sleep(700);
			system("CLS");
			cout << R"(
					     .-""-.
					    / .--. \
					   / /    \ \
					   | |    | |
						  | |.-""-.
						 ///`.::::.`\
						||| ::/  \:: ;
						||; ::\__/:: ;
						 \\\ '::::' /
						  `=':-..-'`
)";

			Sleep(500);
			system("CLS");
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



int main()
{
	Auth();

	system("Color 07");
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

	cout << R"(
					       .--.                   .---.
					   .---|__|           .-.     |~~~|
					.--|===|--|_          |_|     |~~~|--.
					|  |===|  |'\     .---!~|  .--|   |--|
					|%%|   |  |.'\    |===| |--|%%|   |  |
					|%%|   |  |\.'\   |   | |__|  |   |  |
					|  |   |  | \  \  |===| |==|  |   |  |
					|  |   |__|  \.'\ |   |_|__|  |~~~|__|
					|  |===|--|   \.'\|===|~|--|%%|~~~|--|
					^--^---'--^    `-'`---^-^--^--^---'--' 
)";

	do
	{
		int exit = sqlite3_open(s, &DB); //it'll take the address in memory and use it in exec() func. (0x085121 for example)

		cout << setw(60) << "Book's Title: ";
		cin >> b.Title;
		cout << setw(60) << "Book's Author: ";
		cin >> b.Author;
		cout << setw(60) << "Book's Page: ";
		cin >> b.Page;
		cout << setw(60) << "Book's Category: ";
		cin >> b.Category;

		//sqlite3 can catch the variable without an error whether string or int anyway so NO need to specify the page var as a integer.
		string sql("INSERT INTO BOOKS (TITLE, AUTHOR, PAGE, CATEGORY) VALUES('" + b.Title + "','" + b.Author + "','" + b.Page + "','" + b.Category + "'); ");


		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			cerr << setw(60) << "Error Inserting the data." << endl;
			sqlite3_free(messageError);
		}
		else
		{
			cout << setw(60) << "Successfully Recorded!" << endl;
		}




		sqlite3_close(DB);
		wantToContinue = false;
		cout << "					Want to insert data again? yes [y], no [n]" << endl;
		cout << "					Input--> ";
		cin >> inputContinue;
		inputContinue == "y" && "Y" ? wantToContinue = true : false;

	} while (wantToContinue);

	return mainMenu();

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
		"ID INT PRIMARY KEY AUTOINCREMENT, "
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
	ofstream pout;
	pout.open("Print.txt");
	string printData;

	for (i = 0; i < count; i++) {
		printf("The data in column \"%s\" is: %s\n", columns[i], data[i]);
		pout << columns[i] << "= " << data[i] << endl;
	}

	printf("\n");

	pout.close();
	return 0;
}

static int selectData(const char* s)
{

	sqlite3* DB;
	int exit = 0;
	int _selection;
	string _input;

	cout << R"(
					       .--.                   .---.
					   .---|__|           .-.     |~~~|
					.--|===|--|_          |_|     |~~~|--.
					|  |===|  |'\     .---!~|  .--|   |--|
					|%%|   |  |.'\    |===| |--|%%|   |  |
					|%%|   |  |\.'\   |   | |__|  |   |  |
					|  |   |  | \  \  |===| |==|  |   |  |
					|  |   |__|  \.'\ |   |_|__|  |~~~|__|
					|  |===|--|   \.'\|===|~|--|%%|~~~|--|
					^--^---'--^    `-'`---^-^--^--^---'--' 
)";

	exit = sqlite3_open(s, &DB);
	cout << "					WARNING: IF YOU WANT TO PRINT THE DATA, SEARCH WITH ID" << endl;
	cout << "					Options\n					[1]: Print All Books\n					[2]: Search Book by the Title\n					[3]: Search Book by the ID\n					[4]: Search Book by the Category" << endl;

	cout << "					Input --> ";
	cin >> _selection;

	switch (_selection)
	{
	case 1:
		exit = sqlite3_exec(DB, "SELECT * FROM BOOKS", callbackFunc, NULL, NULL); //for all books
		returnToMain();
		break;
	case 2:
		cout << "					Title: ";
		cin >> _input;
		{ //Solution of: transfer of control bypasses initialization
			string sqlTitle("SELECT * FROM BOOKS WHERE TITLE='" + _input + "'");
			exit = sqlite3_exec(DB, sqlTitle.c_str(), callbackFunc, NULL, NULL);
			returnToMain();
		}
		break;
	case 3:
		cout << "					ID: ";
		cin >> _input;
		{
			string sqlID("SELECT * FROM BOOKS WHERE ID='" + _input + "'");
			exit = sqlite3_exec(DB, sqlID.c_str(), callbackFunc, NULL, NULL);
			cout << "Printed to the text file. \n";
			returnToMain();
		}

		break;
	case 4:
		cout << "					Category: ";
		cin >> _input;
		{
			string sqlCategory("SELECT * FROM BOOKS WHERE CATEGORY='" + _input + "'");
			exit = sqlite3_exec(DB, sqlCategory.c_str(), callbackFunc, NULL, NULL);
			returnToMain();
		}

		break;
	}

	sqlite3_close(DB);

	return 0;
}

static int deleteData(const char* s)
{
	system("Color 04");
	sqlite3* DB;
	char* messageError;
	int exit = 0;
	exit = sqlite3_open(s, &DB);

	cout << R"(
					       .--.                   .---.
					   .---|__|           .-.     |~~~|
					.--|===|--|_          |_|     |~~~|--.
					|  |===|  |'\     .---!~|  .--|   |--|
					|%%|   |  |.'\    |===| |--|%%|   |  |
					|%%|   |  |\.'\   |   | |__|  |   |  |
					|  |   |  | \  \  |===| |==|  |   |  |
					|  |   |__|  \.'\ |   |_|__|  |~~~|__|
					|  |===|--|   \.'\|===|~|--|%%|~~~|--|
					^--^---'--^    `-'`---^-^--^--^---'--' 
)";

	cout << "				WARNING: YOU CAN ONLY DELETE A BOOK BY USING ID NUMBER!!\n";
	cout << "				[1] Delete the data by the ID, [2] DELETE ALL DATA IN THE DB\n";
	cout << "					Input --> ";
	string selection;
	string given;
	string sqlDelete;
	cin >> selection;
	if (selection == "1")
	{
		cout << "ID--> ";
		cin >> given;
		sqlDelete = "DELETE FROM BOOKS WHERE BOOKS.ID = '" + given + "'";
		exit = sqlite3_exec(DB, sqlDelete.c_str(), callbackFunc, NULL, &messageError);
		if (exit != SQLITE_OK)
		{
			cout << "delete error";
			sqlite3_free(&messageError);
			return mainMenu();
		}
		else
		{
			cout << "Success!";
		}

		sqlite3_close(DB);


	}
	else if (selection == "2")
	{
		string sure;
		cout << "You sure? yes or no --> ";
		cin >> sure;
		if (sure == "yes")
		{
			cout << "DELETING ALL THE DATA";
			Sleep(500);
			string sqlDeleteAll("DELETE FROM BOOKS");
			exit = sqlite3_exec(DB, sqlDeleteAll.c_str(), callbackFunc, NULL, NULL);
		}
		else { return mainMenu(); }
	}
	else { return mainMenu(); }

	sqlite3_close(DB);

	return 0;
}

static int mainMenu()
{
	system("CLS");
	const char* dir = "C:\\Programming\\UniProject\\Books.db";
	//MENU VARS

	cout << R"(
					       .--.                   .---.
					   .---|__|           .-.     |~~~|
					.--|===|--|_          |_|     |~~~|--.
					|  |===|  |'\     .---!~|  .--|   |--|
					|%%|   |  |.'\    |===| |--|%%|   |  |
					|%%|   |  |\.'\   |   | |__|  |   |  |
					|  |   |  | \  \  |===| |==|  |   |  |
					|  |   |__|  \.'\ |   |_|__|  |~~~|__|
					|  |===|--|   \.'\|===|~|--|%%|~~~|--|
					^--^---'--^    `-'`---^-^--^--^---'--' 
)";
	cout << "					[1] Register a Book press \n					[2] Search a Book press \n					[3] Delete Book from DB press \n					[4] Exit \n";
	int options;
	cout << "					Input-->";
	cin >> options;

	switch (options)
	{
	case 1:
		system("CLS");
		insertData(dir);
		break;
	case 2:
		Sleep(500);
		system("CLS");
		selectData(dir);
		break;
	case 3:
		Sleep(500);
		system("CLS");
		deleteData(dir);
		break;
	case 4:
		exit(0);
	}

	return 0;
}

static int returnToMain()
{
	string answer;
	cout << "				Do you want to return to Main Menu or Exit? [1] Menu, [2] Exit " << endl;
	cout << setw(60) << "Input--> ";
	cin >> answer;

	if (answer == "1")
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