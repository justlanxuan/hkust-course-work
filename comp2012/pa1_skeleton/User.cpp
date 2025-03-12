#include "User.h"
#include "Book.h"
// Task 3.1: done!
User::User():userId(0),name(""),numBooksBorrowed(0),maxBooks(5),booksBorrowed(nullptr)
{
}
// Task 3.2: done!
User::User(int id, const string &n, int borrow, int max): userId(id),name(n),numBooksBorrowed(borrow),maxBooks(max),booksBorrowed(nullptr)
{
}
// Task 3.3: done! check memory leak
User::~User()
{
    for(int i=0;i<numBooksBorrowed;i++){
        delete booksBorrowed[i];
    }
    delete [] booksBorrowed;
}
// Task 3.4: 
void User::borrowBook(Book *book)
{
    if(this->numBooksBorrowed>=this->maxBooks){
        cout<<"You cannot borrow more books."<<endl;
        return;
    }
    else if(book == nullptr){
        cout<<"This book is currently unavailable."<<endl;
        return;
    }
    else{

    }
}

void User::returnBook(Book *book)
{
}

int User::getNumBooksBorrowed() const
{
}

int User::getUserId() const
{
}

string User::getUserName() const
{
}

int User::getMaxBooks() const
{
}

void User::viewBorrowedBooks() const
{
}

void User::giveRating(BookList &list, int bookId, double newRating)
{
}

void User::updateMaxBooks(int additionalSlots)
{
}