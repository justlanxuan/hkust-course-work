#include "Library.h"

// Constructor
Library::Library(int initialCapacity):userCount(0),capacity(initialCapacity),totalRevenue(0),libraryInventory()
{
    users = new User*[this->capacity]{nullptr};
}

// Destructor
Library::~Library()
{
    for(int i=0;i<this->userCount;i++){
        delete users[i];
    }
    delete [] users;
}
// Task 4.3: done!
void Library::addUser(int id, const string &name)
{
    // if the library reached its maximum capacity
    if(this->userCount>=this->capacity){
        User** temp = new User*[this->capacity * 2];
        for(int i=0;i<this->capacity;i++){
            temp[i] = users[i];
        }
        delete [] users;
        users = temp;
        this->capacity *= 2;
    }
    // add users
    users[userCount] = new User(id,name);
    userCount++;
    this->totalRevenue += 5;
    return;
}
// Task 4.4: done!
void Library::upgradeUserSlots(int userId, int additionalSlots)
{
    for(int i=0;i<this->userCount;i++){
        if(this->users[i] == nullptr){
            break;
        }
        if(userId == this->users[i]->getUserId()){
            this->users[i]->updateMaxBooks(additionalSlots);
            this->totalRevenue += additionalSlots;
            cout<<"User ID "<<userId<<" upgraded by "<<additionalSlots<<" slots."<<endl;
            return;
        }
    }
    // not found
    cout<<"User ID "<<userId<<" not found."<<endl;
    return;
}
// Task 4.5: done!
double Library::getTotalRevenue() const
{
    return this->totalRevenue;
}
// Task 4.6: done!
// User ID: 1, Name: Alice, Borrowed Books: 0, Max Books: 5
void Library::displayUsers() const
{
    for(int i=0;i<this->userCount;i++){
        cout<<"User ID: "<<this->users[i]->getUserId()<<", Name: "<<this->users[i]->getUserName()
        <<", Borrowed Books: "<<this->users[i]->getNumBooksBorrowed()<<", Max Books: "<<this->users[i]->getMaxBooks()<<endl;
    }
    return;
    
}
// Task 4.7: done!
User *Library::getUserById(int userId) const
{
    for(int i=0;i<this->userCount;i++){
        if(userId == this->users[i]->getUserId()){
            return this->users[i];
        }
    }
    return nullptr;
}
// Task 4.8: done!(a bit wiered on libraryInventory)
void Library::addNewBook(Book *book)
{
    // fundings
    if(book == nullptr){
        return;
    }
    if(this->totalRevenue < 2){
        cout<<"Insufficient funds to add the book "<<book->getTitle()<<"."<<endl;
        return;
    }
    else{
            libraryInventory.insertBook(book);
            this->totalRevenue -= 2;
            
            cout<<"Book '"<<book->getTitle()<<"' added to the library."<<endl;
            return;    
    }
}
// Task 4.9: done?
void Library::removeBook(int bookId)
{
    // book is not found
    if(libraryInventory.searchList(bookId)==nullptr){
        cout<<"Book with ID"<<bookId<<"not found in the library."<<endl;
        return;
    }
    // the book is found
    if(libraryInventory.searchList(bookId)!=nullptr)
    {
        if(libraryInventory.searchList(bookId)->getInventoryCount() == 0){
            libraryInventory.removeBook(libraryInventory.searchList(bookId));
            return;
        }
        else{
            while(libraryInventory.searchList(bookId)!=nullptr){
        libraryInventory.removeBook(libraryInventory.searchList(bookId));
        this->totalRevenue += 1;
        }
        }
    }
}
// Task 4.10
/**
 * Library Book Details:
ID: 1 - Title: The Great Gatsby - Author: F. Scott Fitzgerald - Rating: 0
ID: 2 - Title: 1984 - Author: George Orwell - Rating: 0
ID: 3 - Title: To Kill a Mockingbird - Author: Harper Lee - Rating: 0
ID: 4 - Title: Great Expectations - Author: Charles Dickens - Rating: 0
 */
void Library::displayBooks() const
{
    cout<<"Library Book Details:"<<endl;
    libraryInventory.displayBooks();
}

BookList &Library::getLibraryInventory()
{
    return libraryInventory;
}