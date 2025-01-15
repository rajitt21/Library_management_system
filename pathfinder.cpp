#include <bits/stdc++.h>
typedef long long int ll;
#define ld long double
#define pb push_back

using namespace std;

struct Date { // A date has day 'd', month 'm' and year 'y'
    int d, m, y;
};

const int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
// To store number of days in all months from January to Dec.


void start();

class Book {  // Definind bok and Book Database classes
public:
	string title;
	string author;
	string isbn;
	string publication;
	bool issued;
	string issued_by;
	Date issue_date;
	Book() {
		issued = false;
	};
};


class Book_db {
public:
	vector <Book> Book_list;
	void Add();
	void Update();
	void Delete();
	void Search();
	void list_books();
};

class User {
public:
	string id;
	string password;
	string name;
};

class Student : public User {
public:
	int total_fine;
	std::vector<Book> books;

	void Calculate_fine();
	void Clear_fine_amount();
	void Issue();
	void Return();
	void list_your_books();
};

class Professor : public User {
public:
	int total_fine;
	std::vector<Book> books;

	void Calculate_fine();
	void Clear_fine_amount();
	void Issue();
	void Return();
	void list_your_books();
};

class Librarian : public User {
public:
	Librarian() { // There would be only 1 librarian
		id = "IndranilSir";
		password = "IsGreat";
		name = "P.K Kelkar";
	};
	bool login();
	void run();
};

class User_db {
private:
	std::vector<Student> Student_list;
	std::vector<Professor> Professor_list;

public:
	void Add();
	void Update();
	void Delete();
	void Search_student();
	void Search_professor();
	void list_users();
	void run_stud();
	void run_prof();
	int login_stud();
	int login_prof();
};

int countLeapYears(Date d) // This function counts number of leap years before the given date
{
    int years = d.y;
 
    // Check if the current year needs to be considered for the count of leap years or not
    if (d.m <= 2)
        years--;
 
    return years / 4 - years / 100 + years / 400;
}

int getDifference(Date dt1, Date dt2) // This function returns number of days between two given dates
{
    long int n1 = dt1.y * 365 + dt1.d;
    for (int i = 0; i < dt1.m - 1; i++)
        n1 += monthDays[i];
    n1 += countLeapYears(dt1);
 
    long int n2 = dt2.y * 365 + dt2.d;
    for (int i = 0; i < dt2.m - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(dt2);
 
    return (n2 - n1);
}

User_db user_data;  //Defining 3 global variables to store database of books and users
Book_db book_data;  // It is done so to reduce the of calling functions



//------------------------------------------------------------------------------------------------------------------------------------------------------



int main(){

	start();

	return 0; 
}

void start() {
	Librarian libn;
	while(true) {
		int work;
		cout << "What do you want me to do?\n" <<
		"Press 1 to login as student\n" <<
		"Press 2 to login as professor\n" <<
		"Press 3 to login as librarian\n" <<
		"Press 0 to exit\n";
		cin >> work;
		switch(work) {
			case 1: user_data.run_stud();
					break;

			case 2: user_data.run_prof();
					break;

			case 3: libn.run();
					break;

			case 0: return;
					break;

			default: cout << "Not a valid input.\n";
		}
	}
	return;
}



//------------------------------------------------------------------------------------------------------------------------------------------------------



void Book_db :: Add() {
	Book b;
	cout << "Input the details of the book you want to add:\nTitle of the book: ";
	getchar();
	getline(cin, b.title);
	cout << "\nAuthor of the book: ";
	getline(cin, b.author);
	cout << "\nISBN of the book: "; // A book with same ISBN cannot be entered twice
		getline(cin, b.isbn);
		cout << "\nPublication of the book: ";
		getline(cin, b.publication);
		Book_list.pb(b);
		cout << "\nBook added successfully.\n";
		return;
	}
void Book_db :: Update() {
	getchar();
	string s;
	cout << "Input the ISBN of the book you want to edit: "; //Book name can be same but isbn of 2 different books need to be different
	getline(cin, s);
	ll i=0;
	for (i = 0; i < Book_list.size(); ++i){
		if(Book_list[i].isbn == s)
			break;
	}
	if(i == Book_list.size())
		cout << "\nNo such book exist.\n";
	else {
		char c;
		cout << "Do you want to change the title of the book? y/n: ";
		cin >> c;
		if(c=='y') {
			cout << "\nEnter new title of the Book: ";
			getchar();
			getline(cin, Book_list[i].title);
		}
		cout << "Do you want to change the author of the book? y/n: ";
		cin >> c;
		if(c=='y') {
			cout << "\nEnter new author of the Book: ";
			getchar();
			getline(cin, Book_list[i].author);
		}
		cout << "Do you want to change the publication of the book? y/n: ";
		cin >> c;
		if(c=='y') {
			cout << "\nEnter new publication of the Book: ";
			getchar();
			getline(cin, Book_list[i].publication);
		}
		cout << "\nBook updated successfully.\n";
	}
}

void Book_db :: Delete() {
	getchar();
	string s;
	cout << "Input the ISBN of the book you want to delete: "; //Book name can be same but isbn of 2 different books need to be different
	getline(cin, s);
	ll i=0;
	for (i = 0; i < Book_list.size(); ++i){
		if(Book_list[i].isbn == s)
			break;
	}
	if(i == Book_list.size())
		cout << "No such book exist.\n";
	else {
		Book_list.erase(Book_list.begin()+i);
		cout << "\nBook deleted successfully.\n";
	}
}

void Book_db :: list_books() {
	cout << "Books:\n";
	for (int i = 0; i < Book_list.size(); ++i)
	{
		cout << i+1 << " " << Book_list[i].title << " - Author: " << Book_list[i].author
		<< "\n   ISBN: " << Book_list[i].isbn << " - Publication: " << Book_list[i].publication << "\n";
		if(Book_list[i].issued)
			cout << "Issued By: " << Book_list[i].issued_by << " - Issue Date: " << Book_list[i].issue_date.d << "/" << Book_list[i].issue_date.m << "/" << Book_list[i].issue_date.y << "/" << "\n";
		else
			cout << "Not Issued\n";
	}
	cout << "Press enter to continue.\n";
	getchar();
	getchar();
}

void Book_db::Search() {
	getchar();
	cout << "Input the title of the book: ";
	string input_name;
	getline(cin, input_name);
	for (int i = 0; i < Book_list.size(); ++i)
	{
		if(input_name == Book_list[i].title) {
			cout << i+1 << " " << Book_list[i].title << " - Author: " << Book_list[i].author
			<< "\n   ISBN: " << Book_list[i].isbn << " - Publication: " << Book_list[i].publication << "\n";
			if(Book_list[i].issued)
				cout << "Issued By: " << Book_list[i].issued_by << " - Issue Date: " << Book_list[i].issue_date.d << "/" << Book_list[i].issue_date.m << "/" << Book_list[i].issue_date.y << "\n";
			else
				cout << "Not Issued\n";

			return;
		}
	}
	cout << "No such book exist.\n";
	return;
}


//-----------------------------------------------------------------------------------------------------------------------------------------------------


bool Librarian :: login() {
	getchar();
	string input_id, input_pass;
	int tries=3;
	while(tries--) {
		cout << "\nLibrarian Login:\nEnter your User Id: ";
		getline(cin, input_id);
		if(input_id != id)
			cout << "Wrong User Id!\n";
		else {
			cout << "Enter your Password: ";
			getline(cin, input_pass);
			if(input_pass != password)
				cout << "Wrong Password!\n";
			else
				return true;
		}
	}
	return false;
}


void Librarian :: run() {
	int valid = 5;
	if(login()) {
		cout << "\nWelcome " << name;
		while(valid) {
			cout << "\nWhat do you want to do?\n"
			<< "Press 1 to list all books.\n"
			<< "Press 2 to add new book.\n"
			<< "Press 3 to update a book.\n"
			<< "Press 4 to delete a book.\n"
			<< "Press 5 to search for a book.\n"
			<< "Press 6 to list all users.\n"
			<< "Press 7 to add new user.\n"
			<< "Press 8 to update a user.\n"
			<< "Press 9 to delete a user.\n"
			<< "Press 10 to search for a student.\n"
			<< "Press 11 to search for a professor.\n"
			<< "Press 0 to logout.\n";

			int work;
			cin >> work;
			switch(work) {
				case 1: book_data.list_books();
				break;

				case 2: book_data.Add();
				break;

				case 3: book_data.Update();
				break;

				case 4: book_data.Delete();
				break;

				case 5: book_data.Search();
				break;

				case 6: user_data.list_users();
				break;

				case 7: user_data.Add();
				break;

				case 8: user_data.Update();
				break;

				case 9: user_data.Delete();
				break;

				case 10: user_data.Search_student();
				break;

				case 11: user_data.Search_professor();
				break;

				case 0: return;
				break;

				default: cout << "Not a valid input.\n";
						valid--;
						break;
			}
		}

	}
	return;
}


//-----------------------------------------------------------------------------------------


void User_db :: Add() {
	getchar();
	cout << "Which type of user you want to add?\nPress 1 for Student\nPress 2 for Professor\n";
	int user_type;
	cin >> user_type;
	if(user_type==1) {
		Student s;
		cout << "Input the details of the user you want to add:\nName: ";
		getchar();
		getline(cin, s.name);
		cout << "\nUser Id: ";
		getline(cin, s.id);
		cout << "\nPassword: ";
		getline(cin, s.password);
		Student_list.pb(s);
		cout << "\nUser added successfully.\n";
	}

	else if(user_type==2){
		Professor s;
		cout << "Input the details of the user you want to add:\nName: ";
		getchar();
		getline(cin, s.name);
		cout << "\nUser Id: ";
		getline(cin, s.id);
		cout << "\nPassword: ";
		getline(cin, s.password);
		Professor_list.pb(s);
		cout << "\nUser added successfully.\n";
	}
	else {
		cout << "Invalid input.\n";
	}
	return;;

}

void User_db :: Update() {
	getchar();
	cout << "Which type of user you want to update?\nPress 1 for Student\nPress 2 for Professor\n";
	int user_type;
	cin >> user_type;
	if(user_type==1) {
		string s;
		cout << "Input the user id of the student you want to edit: "; //Book name can be same but isbn of 2 different books need to be different
		getchar();
		getline(cin, s);
		ll i=0;
		for (i = 0; i < Student_list.size(); ++i){
			if(Student_list[i].id == s)
				break;
		}
		if(i == Student_list.size())
			cout << "\nNo such student exist.\n";
		else {
			char c;
			cout << "Do you want to change the name of the student? y/n: ";
			cin >> c;
			if(c=='y') {
				cout << "\nEnter new name of the student: ";
				getchar();
				getline(cin, Student_list[i].name);
			}
			cout << "Do you want to change the username of the student? y/n: ";
			cin >> c;
			if(c=='y') {
				cout << "\nEnter new username of the student: ";
				getchar();
				getline(cin, Student_list[i].id);
			}
			cout << "Do you want to change the password of the student? y/n: ";
			cin >> c;
			if(c=='y') {
				cout << "\nEnter new password of the student: ";
				getchar();
				getline(cin, Student_list[i].password);
			}
			cout << "\nUser updated successfully.\n";
		}
	}

	else if(user_type==2){
		string s;
		cout << "Input the user id of the Professor you want to edit: "; //Book name can be same but isbn of 2 different books need to be different
		getchar();
		getline(cin, s);
		ll i=0;
		for (i = 0; i < Professor_list.size(); ++i){
			if(Professor_list[i].id == s)
				break;
		}
		if(i == Professor_list.size())
			cout << "\nNo such Professor exist.\n";
		else {
			char c;
			cout << "Do you want to change the name of the Professor? y/n: ";
			cin >> c;
			if(c=='y') {
				cout << "\nEnter new name of the Professor: ";
				getchar();
				getline(cin, Professor_list[i].name);
			}
			cout << "Do you want to change the username of the Professor? y/n: ";
			cin >> c;
			if(c=='y') {
				cout << "\nEnter new username of the Professor: ";
				getchar();
				getline(cin, Professor_list[i].id);
			}
			cout << "Do you want to change the password of the Professor? y/n: ";
			cin >> c;
			if(c=='y') {
				cout << "\nEnter new password of the Professor: ";
				getchar();
				getline(cin, Professor_list[i].password);
			}
			cout << "\nUser updated successfully.\n";
		}
	}
	else {
		cout << "Invalid input.\n";
	}
	return;
}

void User_db :: Delete() {
	getchar();
	cout << "Which type of user you want to add?\nPress 1 for Student\nPress 2 for Professor\n";
	int user_type;
	cin >> user_type;
	if(user_type==1) {
	string s;
	cout << "Input the user id of the student you want to delete: "; //Book name can be same but isbn of 2 different books need to be different
	getchar();
	getline(cin, s);
	ll i=0;
	for (i = 0; i < Student_list.size(); ++i){
		if(Student_list[i].id == s)
			break;
	}
	if(i == Student_list.size())
		cout << "No such student exist.\n";
	else {
		Student_list.erase(Student_list.begin()+i);
		cout << "\nUser deleted successfully.\n";
	}
	}

	else if(user_type==2){
	string s;
	cout << "Input the user id of the professor you want to delete: "; //Book name can be same but isbn of 2 different books need to be different
	getchar();
	getline(cin, s);
	ll i=0;
	for (i = 0; i < Professor_list.size(); ++i){
		if(Professor_list[i].id == s)
			break;
	}
	if(i == Professor_list.size())
		cout << "No such professor exist.\n";
	else {
		Professor_list.erase(Professor_list.begin()+i);
		cout << "\nUser deleted successfully.\n";
	}
	}
	else {
		cout << "Invalid input.\n";
	}
	return;
}

void User_db :: list_users() {
	cout << "Students:\n";
	for (int i = 0; i < Student_list.size(); ++i)
	{
		cout << i+1 << " " << Student_list[i].name << " - User Id: " << Student_list[i].id << "\n";
	}

	cout << "\nProfessors:\n";
	for (int i = 0; i < Professor_list.size(); ++i)
	{
		cout << i+1 << " " << Professor_list[i].name << " - User Id: " << Professor_list[i].id << "\n";
	}
	cout << "Press enter to continue.\n";
	getchar();
	getchar();
}


int User_db :: login_stud() {
	getchar();
	string input_id, input_pass;
	int tries=3;
	while(tries--) {
		cout << "Student Login:\nEnter your User Id: ";
		getline(cin, input_id);
		cout << "Enter your Password: ";
		getline(cin, input_pass);

		for (int i = 0; i < Student_list.size(); ++i) {
			if(Student_list[i].id == input_id && Student_list[i].password == input_pass)
				return i;
		}
		cout << "Invalid credentials.\n";
	}
	return -1;
}

void User_db :: run_stud() {
	int student_index = login_stud(), valid=5;
	if(student_index != -1) {
		while(valid) {
			cout << "\nWelcome " << Student_list[student_index].name;
			cout << "\nWhat do you want to do?\n"
			<< "Press 1 to list all books.\n"
			<< "Press 2 to list books you have.\n"
			<< "Press 3 to issue a book.\n"
			<< "Press 4 to return a book.\n"
			<< "Press 5 to calculate fine imposed.\n"
			<< "Press 6 to pay your fine.\n"
			<< "Press 0 to logout.\n";

			int work;
			cin >> work;
			switch(work) {
				case 1: book_data.list_books();
				break;

				case 2: Student_list[student_index].list_your_books();
				break;

				case 3: Student_list[student_index].Issue();
				break;

				case 4: Student_list[student_index].Return();
				break;

				case 5: Student_list[student_index].Calculate_fine();
				break;

				case 6: Student_list[student_index].Clear_fine_amount();
				break;

				case 0: return;
				break;

				default: cout << "Not a valid input.\n";
						valid--;
						break;
			}
		}

	}
	return;
}


int User_db :: login_prof() {
	getchar();
	string input_id, input_pass;
	int tries=3;
	while(tries--) {
		cout << "Professor Login:\nEnter your User Id: ";
		getline(cin, input_id);
		cout << "Enter your Password: ";
		getline(cin, input_pass);

		for (int i = 0; i < Professor_list.size(); ++i) {
			if(Professor_list[i].id == input_id && Professor_list[i].password == input_pass)
				return i;
		}
		cout << "Invalid credentials.\n";
	}
	return -1;
}

void User_db :: run_prof() {
	int professor_index = login_prof(), valid=5;
	if(professor_index != -1) {
		while(valid) {
			cout << "\nWelcome " << Professor_list[professor_index].name;
			cout << "\nWhat do you want to do?\n"
			<< "Press 1 to list all books.\n"
			<< "Press 2 to list books you have.\n"
			<< "Press 3 to issue a book.\n"
			<< "Press 4 to return a book.\n"
			<< "Press 5 to calculate fine imposed.\n"
			<< "Press 6 to pay your fine.\n"
			<< "Press 0 to logout.\n";

			int work;
			cin >> work;
			switch(work) {
				case 1: book_data.list_books();
				break;

				case 2: Professor_list[professor_index].list_your_books();
				break;

				case 3: Professor_list[professor_index].Issue();
				break;

				case 4: Professor_list[professor_index].Return();
				break;

				case 5: Professor_list[professor_index].Calculate_fine();
				break;

				case 6: Professor_list[professor_index].Clear_fine_amount();
				break;

				case 0: return;
				break;

				default: cout << "Not a valid input.\n";
						valid--;
						break;
			}
		}

	}
	return;
}

void User_db::Search_student() {
	getchar();
	cout << "Input the name of student: ";
	string input_name;
	getline(cin, input_name);
	for (int i = 0; i < Student_list.size(); ++i)
	{
		if(input_name == Student_list[i].name) {
			cout << Student_list[i].name << " - User Id: " << Student_list[i].id
			<< " - Password: " << Student_list[i].password << "\nBooks Issued:\n";
			
			Student_list[i].list_your_books();

			cout << "Do you want to view the fine of the student? y/n: ";
			char c;
			cin >> c;
			if(c=='y') {
				Student_list[i].Calculate_fine();
			}

			return;
		}
	}
	cout << "No such student exist.\n";
	return;
}

void User_db::Search_professor() {
	getchar();
	cout << "Input the name of professor: ";
	string input_name;
	getline(cin, input_name);
	for (int i = 0; i < Professor_list.size(); ++i)
	{
		if(input_name == Professor_list[i].name) {
			cout << Professor_list[i].name << " - User Id: " << Professor_list[i].id
			<< " - Password: " << Professor_list[i].password << "\nBooks Issued:\n";
			
			Professor_list[i].list_your_books();

			cout << "Do you want to view the fine of the professor? y/n: ";
			char c;
			cin >> c;
			if(c=='y') {
				Professor_list[i].Calculate_fine();
			}

			return;
		}
	}
	cout << "No such professor exist.\n";
	return;
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------



void Student :: Issue() {
	cout << "\nEnter today's date(in date month year format): ";
	Date dt;
	cin >> dt.d >> dt.m >> dt.y;
		cout << "Enter the title of book you want to issue.";
		getchar();
		string issue_book;
		getline(cin, issue_book);
		int i;
		for (i = 0; i < book_data.Book_list.size(); ++i){
			if(book_data.Book_list[i].title == issue_book)
				break;
		}
		if(i == book_data.Book_list.size())
			cout << "No such book exist.\n";
		else if(book_data.Book_list[i].issued)
			cout << "This book is already taken by someone else.\n";
		else {
			book_data.Book_list[i].issued = true;
			book_data.Book_list[i].issued_by = name;
			book_data.Book_list[i].issue_date = dt;
			books.pb(book_data.Book_list[i]);
			return;
		}
	return;
}

void Student::Return() {
	cout << "\nEnter today's date(in date month year format): ";
	Date dt;
	cin >> dt.d >> dt.m >> dt.y;
	cout << "Enter the title of book you want to return.";
	getchar();
	string return_book;
	getline(cin, return_book);
	int i, j;
	for (i = 0; i < book_data.Book_list.size(); ++i){
		if(book_data.Book_list[i].title == return_book)
			break;
	}
	for (j = 0; j < books.size(); ++j){
		if(books[j].title == return_book)
			break;
	}
	if(i == book_data.Book_list.size())
		cout << "No such book exist. Again enter the title of the book.\n";
	else if(j == books.size())
		cout << "You don't have any book named " << return_book << ".\n";
	else {
		int days = getDifference(books[i].issue_date, dt);
		cout << "You have to pay fine for this book = " << ((days>30)? (days-30)*2 : 0) << "\n";
		book_data.Book_list[i].issued = false;
		book_data.Book_list[i].issued_by = name;
		books.erase(books.begin()+j);
		return;
	}
}

void Student::Calculate_fine() {
	cout << "\nEnter today's date: ";
	Date dt;
	cin >> dt.d >> dt.m >> dt.y;
	total_fine=0;
	if(books.size()==0) {
		cout << "Fine = " << 0 << "\n";
		return;
	}
	for (int i = 0; i < books.size(); ++i)
	{
		int days = getDifference(books[i].issue_date, dt);
		total_fine += ((days>30)? ((days-30)*2) : 0);
	}
	cout << "Fine = " << total_fine << "\n";
	return;
}

void Student::Clear_fine_amount() {
	total_fine = 0;
	cout << "Fine Cleared!\n";
	return;
}

void Student::list_your_books() {
	cout << "Books Issued:\n";
	for (int i = 0; i < books.size(); ++i)
	{
		cout << i+1 << " " << books[i].title << " - Author: " << books[i].author
		<< "\n   ISBN: " << books[i].isbn << " - Publication: " << books[i].publication << "\n";
		if(books[i].issued)
			cout << "Issue Date: " << books[i].issue_date.d << "/" << books[i].issue_date.m << "/" << books[i].issue_date.y << "\n";
	}
	cout << "Press enter to continue.\n";
	getchar();
	getchar();
	return;
}


// ---------------------------------------------------------------------------------------------------------------------------------------------------



void Professor :: Issue() {
	cout << "\nEnter today's date(in date month year format): ";
	Date dt;
	cin >> dt.d >> dt.m >> dt.y;
		cout << "Enter the title of book you want to issue.";
		getchar();
		string issue_book;
		getline(cin, issue_book);
		int i;
		for (i = 0; i < book_data.Book_list.size(); ++i){
			if(book_data.Book_list[i].title == issue_book)
				break;
		}
		if(i == book_data.Book_list.size())
			cout << "No such book exist.\n";
		else if(book_data.Book_list[i].issued)
			cout << "This book is already taken by someone else.\n";
		else {
			book_data.Book_list[i].issued = true;
			book_data.Book_list[i].issued_by = name;
			book_data.Book_list[i].issue_date = dt;
			books.pb(book_data.Book_list[i]);
			return;
		}
	return;
}

void Professor::Return() {
	cout << "\nEnter today's date(in date month year format): ";
	Date dt;
	cin >> dt.d >> dt.m >> dt.y;
	cout << "Enter the title of book you want to return.";
	getchar();
	string return_book;
	getline(cin, return_book);
	int i, j;
	for (i = 0; i < book_data.Book_list.size(); ++i){
		if(book_data.Book_list[i].title == return_book)
			break;
	}
	for (j = 0; j < books.size(); ++j){
		if(books[j].title == return_book)
			break;
	}
	if(i == book_data.Book_list.size())
		cout << "No such book exist. Again enter the title of the book.\n";
	else if(j == books.size())
		cout << "You don't have any book named " << return_book << ".\n";
	else {
		int days = getDifference(books[i].issue_date, dt);
		cout << "You have to pay fine for this book = " << ((days>60)? (days-60)*5 : 0) << "\n";
		book_data.Book_list[i].issued = false;
		book_data.Book_list[i].issued_by = name;
		books.erase(books.begin()+j);
		return;
	}
}

void Professor::Calculate_fine() {
	cout << "\nEnter today's date: ";
	Date dt;
	cin >> dt.d >> dt.m >> dt.y;
	total_fine=0;
	if(books.size()==0) {
		cout << "Fine = " << 0 << "\n";
		return;
	}
	for (int i = 0; i < books.size(); ++i)
	{
		int days = getDifference(books[i].issue_date, dt);
		total_fine += ((days>60)? ((days-60)*5) : 0);
	}
	cout << "Fine = " << total_fine << "\n";
	return;
}

void Professor::Clear_fine_amount() {
	total_fine = 0;
	cout << "Fine Cleared!\n";
	return;
}

void Professor::list_your_books() {
	cout << "Books Issued:\n";
	for (int i = 0; i < books.size(); ++i)
	{
		cout << i+1 << " " << books[i].title << " - Author: " << books[i].author
		<< "\n   ISBN: " << books[i].isbn << " - Publication: " << books[i].publication << "\n";
		if(books[i].issued)
			cout << "Issue Date: " << books[i].issue_date.d << "/" << books[i].issue_date.m << "/" << books[i].issue_date.y << "\n";
	}
	cout << "Press enter to continue.\n";
	getchar();
	getchar();
	return;
}