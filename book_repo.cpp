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

string book_data[num_books] = { //this takes each set of strings and gives it its own spot on the book_data array
    "F1,Blood Guts & Gore,Ima Fruitcake,39.95,42,37.99,FICTION",
    "N2,Forensics for Housewives,Genevieve Valentin,123.45,99.99,199,NONFICTION",
    "F3,Slipping on Bananas: Iron Part II,Jon Q. Nobody,29.75,32.90,54,FICTION",
    "F4,BEAUTY AND THE BEEF: A Vejji Tale,Dizney Corp,13,14,13.50,FICTION",
    "N5,The Walking Deadhead: Story of my Life,David Bishop,0.99,1.02,-0.01,NONFICTION",
    "N6,Sage & the Infinite Inbox,Sage,1000,999,987.99,NONFICTION"
};

//Repository class that takes everything and stores it all
class Repository {
public:
    int last_index; //index of the last book in the repo
    int capacity; //that max size of the repo
    Book** books; //books is an array of pointers to books; so pointer* to pointer*, could also be done as Book* books[6];
    Repository(); //empty constructor
    Repository(int capacity); //sets max size when constructor used
    void parse_add(string datarow); //parses the book_data strings, creates them as Book objects, and adds them to the repository.
    void print_all(); //prints all books in the repo using each book's print method
    bool remove(string bookID); //is going to remove a book based on book id
    void print_avg_price(string bookID); //prints a specific books avg price
    void print_invalid_prices(); //Locates and prints invalid prices
    void print_by_booktype(BookType btype); //prints all books by specified type
    ~Repository(); //Destructor that destroys the repo
};

Repository::Repository() { //empty constructor that sets all attributes to default values
    this->capacity = 0;
    this->last_index = -1; //this means its empty
    this->books = nullptr;
}

Repository::Repository(int capacity) { //sets max cap of repo
    this->capacity = capacity; //inflexible, initializes the repo with this limited value
    this->last_index = -1; //again, empty
    this->books = new Book * [capacity]; 
}

void Repository::parse_add(string datarow) {
    if (last_index < capacity) {
        last_index += 1;
        double temp_price_array[Book::priceArraySize]; //temp array to hold prices for each book
        //Tests if fiction or nonfiction using book ID, cannot create anything of type 'Book'
        //Makes the appropriate object now using constructor
        //WILL PROBABLY NEED TO ADD A SECTION FOR PARSING THE ENUM TYPE FOR THE FINAL PROJECT
        if (datarow[0] == 'F') {
            this->books[last_index] = new Book();
            books[last_index]->set_btype(FICTION);
        }
        else if (datarow[0] == 'N') {
            this->books[last_index] = new Book();
            books[last_index]->set_btype(NONFICTION);
        }
        else {
            std::cerr << "INVALID BOOK TYPE - EXITING NOW\n";
            exit(-1);
        }

        //Parses through each book string, seperating them at the comma that separates attributes
        //We will then extract each of these substrings and set each as an attribute
        //The below logic moves through each book_data string from left to right so, ID, TITLE, Author, Prices, BookType
        //Sets the ID
        int right_side = book_data[last_index].find(","); //named rightside because it is the right hand side of the substring, sits on the comma
        books[last_index]->set_book_ID(book_data[last_index].substr(0, right_side));

        //gets and sets the title
        int left_side = right_side + 1; //the left side of the substring
        right_side = book_data[last_index].find(",", left_side);
        books[last_index]->set_title(book_data[last_index].substr(left_side, right_side - left_side));

        //gets and sets the author
        left_side = right_side + 1;
        right_side = book_data[last_index].find(",", left_side);
        books[last_index]->set_author(book_data[last_index].substr(left_side, right_side - left_side));

        //gets the prices
        //EAACH PRICE MUST BE CONVERTED TO A DOUBLE with stod() function
        //element 1
        left_side = right_side + 1;
        right_side = book_data[last_index].find(",", left_side);
        temp_price_array[0] = std::stod(book_data[last_index].substr(left_side, right_side - left_side));
        //element2
        left_side = right_side + 1;
        right_side = book_data[last_index].find(",", left_side);
        temp_price_array[1] = std::stod(book_data[last_index].substr(left_side, right_side - left_side));
        //element3
        left_side = right_side + 1;
        right_side = book_data[last_index].find(",", left_side);
        temp_price_array[2] = std::stod(book_data[last_index].substr(left_side, right_side - left_side));
        //sets the prices
        books[last_index]->set_prices(temp_price_array);
    }
    else {
        std::cerr << "ERROR LIST HAS EXCEED MAX CAPACITY!\n EXITING NOW";
        exit(-1);
    }
}

void Repository::print_all() {
    for (int i = 0; i <= this->last_index; i += 1) {
        (this->books)[i]->print();
    }
}

int main() {
    Repository* repo = new Repository(num_books); // MAKES THE REPOSITORY and REPO IS A POINTER TO IT

    cout << "Parsing data and adding books: \t"; //Flavor text, \t is a horizontal tab
    for (int i = 0; 1 < num_books; i += 1) {
        repo->parse_add(book_data[i]); //Parses each line of the book data, adds them to the repo as book objects
    }
    cout << "DONE!" << std::endl;

}