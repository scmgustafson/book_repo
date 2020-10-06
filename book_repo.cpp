#include <iostream>
#include <iomanip>
#include <string>

using std::string;
using std::cout;
using std::left;
using std::setw;

enum BookType { UNDECIDED, FICTION, NONFICTION };
static const std::string book_type_strings[] = { "UNDECIDED", "FICTION", "NONFICTION" }; //this is created so we can retreive the name of a "BookType" rather than its numerical enum value

class Book {
private:
    string bookID;
    string title;
    string author;
    double* prices; //not sure why this is set up as a ptr
    BookType btype;

public:
    const static int priceArraySize = 3;
    Book(); //empty constructor
    Book(string ID, string title, string author, double prices[], BookType type); //full constructor

    //setters for each attribute
    void set_book_ID(string ID);
    void set_title(string title);
    void set_author(string author);
    void set_prices(double prices[]);
    void set_btype(BookType btype);
    void print(); //not sure why this is here

    //getters for each attribute
    string get_book_ID();
    string get_title();
    string get_author();
    double* get_prices(); //not sure why this is set up as a ptr
    BookType get_btype();

    //destructor
    ~Book();
};

//Empty Constructor, or constructor that sets everything with default values
Book::Book() {
    this->bookID = "";
    this->title = "";
    this->author = "";
    this->prices = new double[priceArraySize]; //this creates a new array dynamically, per object created rather than being defined in class
    for (int i = 0; i < priceArraySize; i += 1) { //this for loop iterates through the above array and sets a default price of 0
        this->prices[i] = 0;
    }
    this->btype = UNDECIDED; //enums should have a 0 type, or something that indicates it is a default setting, partially bc enum values are given numerical values starting at 0
}

//Full constructor, sets all values via parameters
Book::Book(string ID, string title, string author, double prices[], BookType type) //I THINK THESE VALUES SHOULD BE NEW_VALUE TO AVOID CONFUSION
{                                                                                  //The "This->" portion of this allows for these parameters to be the same name as the object attribute name
    this->bookID = ID;
    this->title = title;
    this->author = author;
    this->prices = new double[priceArraySize];
    for (int i = 0; i < priceArraySize; i += 1) {
        this->prices[i] = prices[i];
    }
    this->btype = type;
}

//Getters
string Book::get_book_ID() {
    return bookID;
}
string Book::get_title() {
    return title;
}
string Book::get_author() {
    return author;
}
double* Book::get_prices() {
    return prices;
}
BookType Book::get_btype() {
    return btype;
}

//Setters
void Book::set_book_ID(string new_ID) {
    this->bookID = new_ID;
}
void Book::set_title(string new_title) {
    this->title = new_title;
}
void Book::set_author(string new_author) {
    this->author = new_author;
}
void Book::set_prices(double new_prices[]) {
    this->prices = new double[priceArraySize];
    for (int i = 0; i < priceArraySize; i += 1) {
        this->prices[i] = new_prices[i];
    }
}
void Book::set_btype(BookType new_btype) {
    btype = new_btype;
}

//Print method for printing out an object
void Book::print() {
    //left aligns text to the left
    //setw(x) assigns x amount of characters space to that "tab"
    cout << left << setw(5) << bookID;
    cout << left << setw(45) << title;
    cout << left << setw(20) << author;
    cout << left << setw(10) << prices[0];
    cout << left << setw(10) << prices[1];
    cout << left << setw(10) << prices[2];
    cout << left << setw(20) << book_type_strings[get_btype()]; //again, this string was created at top. Used to return the string of BookType rather than the enum value
                                                                //However, get_btype() returns an enum value which will correspond to the index of this string array
}

//The book destructor
Book::~Book() {
    if (prices != nullptr) { //this means if prices has a pointer value, delete it when the destructor is called and then assign it the nullptr value
        delete[] prices;
        prices = nullptr;
    }
}

//NOW WE BEGIN EVERYTHING ABOUT THE REPOSITORY CLASS
const int num_books = 6; //this will correspond to the items on the student data table (number of unique students) V amounts of books down below

string book_data[num_books] = { //this each set of strings and gives it its own spot on the book_data array
    "F1,Blood Guts & Gore,Ima Fruitcake,39.95,42,37.99,FICTION",
    "N2,Forensics for Housewives,Genevieve Valentin,123.45,99.99,199,NONFICTION",
    "F3,Slipping on Bananas: Iron Part II,Jon Q. Nobody,29.75,32.90,54,FICTION",
    "F4,BEAUTY AND THE BEEF: A Vejji Tale,Dizney Corp,13,14,13.50,FICTION",
    "N5,The Walking Deadhead: Story of my Life,David Bishop,0.99,1.02,-0.01,NONFICTION",
    "N6,Sage & the Infinite Inbox,Sage,1000,999,987.99,NONFICTION"
};


int main() {
    


}
