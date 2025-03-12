#include "Book.h"
/**
class Book
{
private:
    int bookId;
    string title;
    string author;
    int inventoryCount;
    double rating;
    int ratingCount;

public:
    // Default constructor
    Book();

    // Constructor
    Book(int id, const string &t, const string &a, int invcount = 1, double rating = 0.0, int ratcount = 0);

    // Member functions
    int getId() const;
    int getInventoryCount() const;
    void changeInventoryCount(int c);
    string getTitle() const;
    string getAuthor() const;
    double getRating() const;
    void addRating(double newRating);
};
 */
// Task 1.1: done!
Book::Book():bookId(0), title(""),author(""),inventoryCount(1),rating(0),ratingCount(0)
{
}
// Task 1.2: done!
Book::Book(int id, const string &t, const string &a, int count, double rat, int ratCount):bookId(id),title(t),author(a),inventoryCount(count),rating(rat),ratingCount(ratCount)
{
}
// Task 1.3: done!
int Book::getId() const
{
    return this->bookId;
}
// Task 1.4: done!
int Book::getInventoryCount() const
{
    return this->inventoryCount;
}
// Task 1.5: done!
void Book::changeInventoryCount(int c)
{
    this->inventoryCount +=c;
}
// Task 1.6: done!
string Book::getTitle() const
{
    return this->title;
}
// Task 1.7: done!
string Book::getAuthor() const
{
    return this->author;
}
// Task 1.8: done!
double Book::getRating() const
{
    return this->rating;
}
// Task 1.9: done!
void Book::addRating(double newRating)
{
    // check the newRating
    if(newRating >=0 && newRating <=5){
        
        this->rating = ((this->rating * this->ratingCount)+newRating)/(ratingCount+1);
        this->ratingCount++;
    }
    else{
        cout<<"Rating must be between 0 and 5."<<endl;
    }
}