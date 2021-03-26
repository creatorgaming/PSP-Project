// Copyright 2021 
// Author: Divyanshu Tyagi

#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <vector>
using namespace std;

// Maximum length of different strings that we can input in the book shop
// Application of Macro in C++
#define MAX_LENGTH 1000	

// Main Parent Class in Book Shop that stores all the important details realted to all the books and revenue
class BookShop {
	public :
	// Application of static member function variable
		static void updateBookShop(double rev, int bS) {
			BookShop::revenue += rev;
			BookShop::bookSold += bS;
		}
		static const double getRevenue(){return revenue;}
		static const int getBookSold(){return bookSold;}

	private :
	// Application of static variable
		static double revenue;
		static int bookSold;
};
// Instansiating static variable
double BookShop::revenue;
int BookShop::bookSold;

// AdminCredentials class stores all the details realted to credentials that Admin need to edit the book shop records
// Application of virtual functions and abstract class
class AdminCredentials {
	public :
		AdminCredentials(string name, int pin) : name{name}, pin{pin}{}
		virtual void updateName(string name) = 0;
		virtual void updatePin(int x) = 0;
	protected :
		string name;
		int pin;
};

// Admin is the derived class of AdminCredentials that depicts individual identity of an Admin
// Application of Inheritance
class Admin : public AdminCredentials, public BookShop {
	public :
	// We don't want user to make an admin without any name or password, hence we deleted its default constructor
		Admin() = delete;
		Admin(string name,int pin) : AdminCredentials(name, pin){}
	// Application of destructor
		~Admin() {name = nullptr; pin = 0;}

		void AdminMenu();
	// Defining base class virtual functions in derived class
		void updateName(string);
		void updatePin(int);

		static void viewBookShopAccount();
	// constant function returning constant data type
		string const getName() const {return this->name;}
		int const getPin() const {return this->pin;};
		void setPin(int pin) {this->pin = pin;}
};

// Book class is derived from BookShop class and has all the nessary functions and variables that inidividual book need 
// Application of Inheritance
class Book : public BookShop {
	public:	
		Book() : author{new char[MAX_LENGTH]}, title{new char[MAX_LENGTH]}, publisher{new char[MAX_LENGTH]}{}
		Book(char* title, char* author, char* publisher, double price, int stock) : title{title}, author{author}, publisher{publisher}, price{price}, stock{stock}{}

		void enterBooks();	
		void editBook();
		void buyBook();
		void showData() const;

		static void printBooks(const vector<Book>&);
		static int search(const vector<Book>&,char*,char*);
		static bool deleteBook(vector<Book>&,int);
	
	// Application of friend function and operator overloading
		friend ostream& operator << (ostream&,const Book&);
		friend istream& operator >> (istream&,Book&);

	// Application of getters and setters
		const char* getTitle() {return title;}
		const char* getAuthor() {return author;}
		const char* getPublisher() {return publisher;}
		const double getPrice() {return price;}
		const int getStock() {return stock;}
	private:
		char *author,*title,*publisher;
		double price;
		int stock;
};

ostream& operator << (ostream& out, const Book& book) {
	out << "-----------------------------------------" << endl;
	out << "Title : " << book.title << endl;
	out << "Author : " << book.author << endl;
	out << "Publisher : " << book.publisher << endl;
	out << "Price : Rs." << book.price << endl;
	out << "Stock : " << book.stock << endl;
	out << "-----------------------------------------" << endl;
	return out;
}

istream& operator >> (istream& in, Book& book) {
	in.ignore();
	cout<<"Enter Title Name: ";       
	in.getline(book.title,MAX_LENGTH);
	cout<<"Enter Author Name: ";      
	in.getline(book.author,MAX_LENGTH);
	cout<<"Enter Publisher Name: ";   
	in.getline(book.publisher,MAX_LENGTH);
	cout<<"Enter Price: ";            
	in>>book.price;
	cout<<"Enter Stock Position: ";   
	in>>book.stock;   
	return in;
}

int Book::search( const vector<Book>& books, char* tbuy,char* abuy)	{
	for(int i = 0; i < books.size(); i++) {
		if(strcmp(books[i].title,tbuy)==0 && strcmp(books[i].author,abuy)==0)
			return i;
	}
	return -1;	
}

// Enter New Books to the record
void Book::enterBooks()	{
	cin.ignore();
	cout<<"Enter Title Name: ";       
	cin.getline(this->title,MAX_LENGTH);
	cout<<"Enter Author Name: ";      
	cin.getline(this->author,MAX_LENGTH);
	cout<<"Enter Publisher Name: ";   
	cin.getline(this->publisher,MAX_LENGTH);
	cout<<"Enter Price: ";            
	cin>>this->price;
	cout<<"Enter Stock Position: ";   
	cin>>this->stock;   
}

// Edit any book within the book shop record
void Book::editBook()	{
	int choice;
	cout << "\n--------------------------------------------------------\n";
	cout << "Which Field you want to edit :- "
		<< "\n1. Author Name"
		<< "\n2. Tile of book"
		<< "\n3. Publisher Name"
		<< "\n4. Price of Book"
		<< "\n5. Stock Position of Book";
	cout << "\n--------------------------------------------------------\n";
	cout << "Enter your choice --> ";
	cin >> choice;
	// To clear input buffer we use cin.ignore()
	cin.ignore();
	switch (choice) {
		case 1:{
			char* str = new char[MAX_LENGTH];
			cout<<"\nEnter Vaild NEW Author Name: ";      
			cin.getline(str,MAX_LENGTH);
			author = str;
			break;
		}
		case 2: {
			char *str = new char[MAX_LENGTH];
			cout<<"\nEnter NEW Title: ";       
			cin.getline(str,MAX_LENGTH);
			title = str;
			break;
		}
		case 3: {
			char *str = new char[MAX_LENGTH];
			cout<<"\nEnter NEW Publisher Name: ";   
			cin.getline(str,MAX_LENGTH);
			publisher = str;
			break;
		}
		case 4: {
			cout << "\nEnter NEW Price of the book: ";            
			cin >> this->price;
			break;
		}
		case 5: {
			cout<<"\nEnter NEW Stock Position: ";   
			cin>>this->stock;   
		}
		default:
			break;
	}
	cout << "\n\n\t\t BOOK RECORD AFTER UPDATION ..." << endl;
	this->showData();
}

void Book::showData() const{
	cout << "-----------------------------------------" << endl;
	cout << "Title : " << this->title << endl;
	cout << "Author : " << this->author << endl;
	cout << "Publisher : " << this->publisher << endl;
	cout << "Price : Rs." << this->price << endl;
	cout << "Stock : " << this->stock << endl;
	cout << "-----------------------------------------" << endl;
}

// Function that Implements the functionality of Buying a book from the shop and printing the bill
void Book::buyBook()	{
	int count;
	cout<<"\nEnter Number Of Books to buy: ";
	cin>>count;
	if(count <= this->stock)	{
		this->stock -= count;
		double total_price = (this->price)*count;
		cout<<"\nBooks Bought Sucessfully";
		cout<<"\nAmount: Rs. "<< total_price;
		updateBookShop(total_price,count);
	}else	cout<<"\n!! Required Copies not in Stock !!" << endl;
}

// Function that implements the functionality of deleting a book within the system
bool Book::deleteBook(vector<Book> &books, int index) {
	if(index == books.size()-1) {
		books.pop_back();
	}else if (index >= 0 && index < books.size()){
		// before deleting any book we need to shift the records first
		for(int i = index; i < books.size(); i++) {
			books[i] = books[i+1];
		}	
		books.pop_back();
	}else {
		return false;
	}
	return true;
}

// Print all the books currently present in the system
void Book::printBooks(const vector<Book> &books) {
	if(books.size() > 0) {
		cout << "**************************************************************************************************" << endl;
		for(int i = 0; i < books.size(); i++) {
			cout << "-----------------------------------------" << endl;
			cout << "SNO. : " << i+1 << endl;
			// cout << "Title : " << books[i].title << endl;
			// cout << "Author : " << books[i].author << endl;
			// cout << "Publisher : " << books[i].publisher << endl;
			// cout << "Price : Rs." << books[i].price << endl;
			// cout << "Stock : " << books[i].stock << endl;
			// cout << "-----------------------------------------" << endl;
			cout << books[i];
		}
		cout << "**************************************************************************************************" << endl;
	}else {
		cout << "!! No Record Found !! " << endl;
	}
}

// Setting of name of admin credential
void Admin::updateName(string name) {
	this->name = name;
}

// Setting of pin of admin credential
void Admin::updatePin(int pin) {
	this->pin = pin;
}

// Function implementing Admin Menu functionality
void Admin::AdminMenu() {
	int choice{0};
	bool inLoop{true};
	while(inLoop) {
		cout << "\n--------------------------------------------------------\n";
		cout << "\t     !!!! [" << this->name << "] !!!!" << endl; 
		cout << "\n\t\t!!!! ADMIN MENU !!!!\n" << endl
			 << "1. Show Book Shop Account Details" << endl
			 << "2. Change Admin Password" << endl
			 << "3. Change Admin Name" << endl
			 << "0. Exit from Admin Menu" << endl;
		cout << "\n--------------------------------------------------------\n";
		cout <<"Enter your Choice --> ";
		cin >> choice;

		switch(choice) {
			case 1:
				Admin::viewBookShopAccount();
				break;
			case 2: {
				int x;
				cout << "Enter new password : ";
				cin >> x;
				this->updatePin(x);
			}
				break;
			case 3: {
				cin.ignore();
				char newName[MAX_LENGTH];
				cout << "Enter new name : ";
				cin.getline(newName,MAX_LENGTH);
				this->updateName(newName);
			}
				break;
			case 0:
				inLoop = false;
				break;
			default:
				cout << "\n\n\t\t !!! WRONG CHOICE !!! \n\n";
				break;
		}
	}
}

// Function showing current details of book shop
void Admin::viewBookShopAccount() {
	cout << "\n--------------------------------------------------------\n";
	cout << "\nTotal Revenue of Book Shop : Rs." << getRevenue();
	cout << "\nTotal number of copies sold : " << getBookSold() << endl;
	cout << "\n--------------------------------------------------------\n";
}

int main()	{
	// Making one Admin by default : Starting of code
	Admin A((char*)"Divyanshu Tyagi", 123);
	
	// Initializing book vector with some records just to easy the implementation and testing
	vector<Book> B {
		Book((char*)"Eloquent JavaScript, Second Edition", (char*)"Marijn Haverbeke", (char*)"No Starch Press", 45.91, 3),
        Book((char*)"Anna Karenina", (char*)"Tolstoy", (char*)"Harcourt Brace", 13.5, 4),
        Book((char*)"Bleak House", (char*)"Dickens, Charles", (char*)"Random House", 5.75, 8),
        Book((char*)"Harry Potter", (char*)"Rowling, J.K",(char*) "Harcourt Brace", 19.95, 4),
        Book((char*)"Lord of the Rings",(char*) "Tolkien, J.R.",(char*) "Penguin", 27.45, 1),
        Book((char*)"Tom Sawyer",(char*) "Twain, Mark",(char*) "Random House", 7.75, 3),
        Book((char*)"One Hundred Years of Solitude",(char*) "Marquez",(char*) "Harper  Perennial", 14.00, 4),
        Book((char*)"Speaking JavaScript",(char*) "Axel Rauschmayer", (char*)"O'Reilly Media", 35.22, 5),
        Book((char*)"The Hours", (char*)"Cunnningham",(char*) "Harcourt Brace", 12.35, 2),
        Book((char*)"Huckleberry Finn", (char*)"Twain",(char*) "Penguin", 5.76, 6)
	};

	// Un-comment the code below and comment the one above if we want to start from scratch 
    // vector<Book> B;

	char titlebuy[MAX_LENGTH],authorbuy[MAX_LENGTH];

	// Main infinite loop of book Shop
	while(1)	{
		char choice;
		cout << "\n--------------------------------------------------------\n";
		cout<<"\t\t|||| MENU ||||\t\t\t[[[[ [A]-ADMIN ]]]]"
		    <<"\n1. Entry of New Book"
		    <<"\n2. Buy Book"
		    <<"\n3. Search For Book"
		    <<"\n4. Edit Details Of Book"
            <<"\n5. Delete Book"
			<<"\n6. Print All Books Details"
		    <<"\n0. Exit";
		cout << "\n--------------------------------------------------------\n";
		cout <<"Enter your Choice --> ";
		cin>>choice;
		
		switch(choice)	{
			case 'A': {
				int pin;
				cout << "Enter admin pin : ";
				cin >> pin;
				if(pin == A.getPin()) {
					cout << "\n\t    !!!! LOGIN SUCCCESSFUL !!!!" << endl;
					A.AdminMenu();
				}else {
					cout << "\n\t\t!!!! INVAILD PASSWORD !!!!" << endl;
				}
				break;
			}
			case '1': {
				Book temp;
				cin >> temp;
                B.push_back(temp);
				break;
			}	
			case '2': {
				cin.ignore();
				cout<<"\nEnter Title Of Book: "; 
                cin.getline(titlebuy,MAX_LENGTH);
				cout<<"Enter Author Of Book: ";  
                cin.getline(authorbuy,MAX_LENGTH);
				int BookIndex = Book::search(B,titlebuy,authorbuy);
				if(BookIndex != -1) {
					if(B[BookIndex].getStock() > 0)
						B[BookIndex].buyBook();
					else 
						cout<<"\n!! Required Copies not in Stock !!" << endl;
				}
				else
					cout<<"\n!! This Book is Not in our RECORD !!";	
				break;
			}
			case '3': {
				cin.ignore();
				cout<<"\nEnter Title Of Book: "; 
                cin.getline(titlebuy,MAX_LENGTH);
				cout<<"Enter Author Of Book: ";  
                cin.getline(authorbuy,MAX_LENGTH);
				int BookIndex = Book::search(B,titlebuy,authorbuy);
				if(BookIndex != -1)
					B[BookIndex].showData();
				else
					cout<<"\n!! This Book is Not in our RECORD !!";	
				break;
			} 
			case '4': {
				cin.ignore();
				cout<<"\nEnter Title Of Book: "; 
                cin.getline(titlebuy,MAX_LENGTH);
				cout<<"Enter Author Of Book: ";  
                cin.getline(authorbuy,MAX_LENGTH);
				int BookIndex = Book::search(B,titlebuy,authorbuy);
				if(BookIndex != -1) 
					B[BookIndex].editBook();
				else 
					cout<<"\n!! This Book is Not in our RECORD !!";	
				break;
			} 
			case '5': {
            	cin.ignore();
				cout<<"\nEnter Title Of Book: "; 
                cin.getline(titlebuy,MAX_LENGTH);
				cout<<"Enter Author Of Book: ";  
                cin.getline(authorbuy,MAX_LENGTH);
				int BookIndex = Book::search(B,titlebuy,authorbuy);
				if(BookIndex != -1)  {
					if(Book::deleteBook(B, BookIndex)) {
						cout << "\n\n\t\tBook Successfully Deleted!!\n" << endl;
					}else {
						cout << "\n\n\t\t!! ERROR WHILE DELETING BOOK !!\n" << endl;
					}
				}else 	cout<<"\n!! This Book is Not in our RECORD !!";	
				break;
			}
			case '6': {
				Book::printBooks(B);
				break;
			}
			case '0': 
				exit(0);
			default: 
				cout<<"\nInvalid Choice Entered";
		}
	}	
	return 0;
}