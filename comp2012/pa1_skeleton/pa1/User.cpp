#include "User.h"
#include "Book.h"
// Task 3.1: done!
User::User():userId(0),name(""),numBooksBorrowed(0),maxBooks(5)
{
    this->booksBorrowed = new Book*[this->maxBooks];
}
// Task 3.2: done!
User::User(int id, const string &n, int borrow, int max): userId(id),name(n),numBooksBorrowed(borrow),maxBooks(max)
{
    this->booksBorrowed = new Book*[this->maxBooks];
}
// Task 3.3: done! check memory leak
User::~User()
{
    delete [] booksBorrowed;
}
// Task 3.4: not specify inventory count = 0
void User::borrowBook(Book *book)
{
    if(this->numBooksBorrowed>=this->maxBooks){
        cout<<"You cannot borrow more books."<<endl;
        return;
    }
    // if book is not in the book list
    else if(book == nullptr){
        cout<<"This book is currently unavailable."<<endl;
        return;
    }
    else if(book->getInventoryCount() <= 0){
        cout<<"This book is currently unavailable."<<endl;
        return;
    }
    else{
        cout<<"Successfully borrowed: "<<book->getTitle()<<endl;
        book->changeInventoryCount(-1);
        booksBorrowed[numBooksBorrowed] = book;
        this->numBooksBorrowed += 1;
        return;
    }
}
// Task 3.5: done!
void User::returnBook(Book *book)
{
    for(int i=0;i<this->numBooksBorrowed;i++){
        if(this->booksBorrowed[i] == nullptr){
            continue;
        }
        if(this->booksBorrowed[i]->getId()==book->getId()){
            cout<<"Successfully returned: "<<book->getTitle()<<endl;
            book->changeInventoryCount(1);
            for(int j=i;j<this->numBooksBorrowed-1;j++){
                this->booksBorrowed[j] = this->booksBorrowed[j+1];
            }
            this->numBooksBorrowed -= 1;
            this->booksBorrowed[numBooksBorrowed] = nullptr;
            return;
        }
    }
    cout<<"This book was not borrowed by you."<<endl;
    return;
}
// Task 3.6:done!
int User::getNumBooksBorrowed() const
{
    return this->numBooksBorrowed;
}
// Task 3.7: done!
int User::getUserId() const
{
    return this->userId;
}
// Task 3.8: done!
string User::getUserName() const
{
    return this->name;
}
// Task 3.9: done!
int User::getMaxBooks() const
{
    return this->maxBooks;
}
// Task 3.10: need to check
void User::viewBorrowedBooks() const
{
    // not borrowed any book
    if(this->numBooksBorrowed == 0){
        cout<<this->name<<" has not borrowed any books."<<endl;
        return;
    }
    int counts[this->numBooksBorrowed] = {0};
    Book* uniqueBooks[this->numBooksBorrowed] = {nullptr};
    int uniqueCount = 0;
    for(int i=0;i<this->numBooksBorrowed;i++){
        bool found = false;
        for(int j=0;j<uniqueCount;j++){
            if(uniqueBooks[j] == this->booksBorrowed[i]){// book is found in unique books
                counts[j]++;
                found = true;
            }
        }
        if(found == false){
        counts[uniqueCount] += 1;
        uniqueBooks[uniqueCount] = this->booksBorrowed[i];
        uniqueCount+=1;
        }
    }    
    // begin print
    cout<<this->name<<"'s Borrowed Books: "<<endl;
    for(int i=0;i<uniqueCount;i++){
        cout<<uniqueBooks[i]->getTitle()<<" (x"<<counts[i]<<")"<<endl;
    }
    return;
}
// Task 3.11: done!
void User::giveRating(BookList &list, int bookId, double newRating)
{
    // if user is blocked
    if(this->numBooksBorrowed>=this->maxBooks){
        cout<<"User is blocked and cannot rate books."<<endl;
        return;
    }
    // if user is not blocked, he can rate
    list.rateBook(bookId,newRating);
}
// Task 3.12: done!
void User::updateMaxBooks(int additionalSlots)
{
    Book** temp_books_borrowed = new Book*[this->maxBooks+additionalSlots];
    for(int i=0;i<this->maxBooks;i++){
        temp_books_borrowed[i] = this->booksBorrowed[i];
    }
    this->maxBooks += additionalSlots;
    delete [] booksBorrowed;
    booksBorrowed = temp_books_borrowed;
    cout<<"Max books updated to: "<<this->maxBooks<<endl;
}