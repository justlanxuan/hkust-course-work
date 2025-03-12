#include "BookList.h"
#include "Book.h"
/**
 * enum SortCriteria
{
    BY_RATING,
    BY_TITLE
};

class BookList
{
private:
    struct Node
    {
        Book *data;
        Node *next;
        Node(Book *book) : data(book), next(nullptr) {}
    };

    Node *head;

public:
    // constructor
    BookList();

    // deep copy constructor
    BookList(const BookList &other);

    // destructor
    ~BookList();

    // Member functions
    bool isEmpty() const;
    void insertBook(Book *book);
    void removeBook(Book *book);
    void displayBooks() const;
    void sortBooks(SortCriteria criteria);
    Book *searchList(int bookId) const;
    int countBooks() const;
    void rateBook(int bookId, double newRating);
    Book *getBookWithMaxRating() const;
    Book *getBookWithMinRating() const;
    void reverseBooksByRating();
};
 */
// Task 2.1: done!
BookList::BookList():head(nullptr)
{
}
// Task 2.2: done!
BookList::BookList(const BookList &other)
{
    if (other.isEmpty()){
        return;
    }
    else{
        this->head = new Node(other.head->data);
        Node* this_list = this->head;
        Node* other_list = other.head->next;
        while(other_list != nullptr){
            this_list->next = new Node(other_list->data);
            other_list = other_list->next;
            this_list = this_list->next;
    }  
    } 
}
// Task 2.3: done! check memory leak
BookList::~BookList()
{
    Node* current = this->head;
    while(current != nullptr){
        Node* temp_next = current->next;
        delete current;
        current = temp_next;
    }
}
// Task 2.4: done!
bool BookList::isEmpty() const
{
    if (this->head == nullptr){
        return true;
    }
    else{
        return false;
    }
}
// Task 2.5: done! check assignment
void BookList::insertBook(Book *book)
{
    // if book exist, increase inv
    Book* search_book = searchList(book->getId());
    if(search_book!=nullptr){
        search_book->changeInventoryCount(1);
        return;
    }
    // if book does not exist, add an objext
    else{
        if(this->isEmpty()){
            this->head = new Node(book);
        }
        else{
            Node* current = this->head;
            while(current->next != nullptr){
                current = current->next;
            }
            current->next = new Node(book);
        }
        return;
    }
}
// Task 2.6: done! check memory leak
void BookList::removeBook(Book *book)
{
    // book not found
    if(searchList(book->getId())==nullptr){
        return;
    }
    else{
        book->changeInventoryCount(-1);
        int num_of_book = book->getInventoryCount();
        if(num_of_book = 0){// remove the book
            Node* current = this->head;
            while(current != nullptr){
                if(current->data->getId()==book->getId()){
                    Node* temp_next = current->next;
                    delete current;
                    current = temp_next;
                    break;
                }
                current = current->next;
            }
            
        }
        else{
            return;
        }
    }
}
// Task 2.7: done!
void BookList::displayBooks() const
{
    cout<<"Library Book Details:"<<endl;
    if(this->isEmpty()){
        cout<<"The book list is empty."<<endl;
    }
    else{
        Node* current = this->head;
        while(current != nullptr){
            cout<<"ID: "<<current->data->getId()<<" - Title: "<<current->data->getTitle()<<" - Author: "<<current->data->getAuthor()<<" - Rating: "<<current->data->getRating()<<endl;
            current = current->next;
        }
    }    
}
// Task 2.8:
void BookList::sortBooks(SortCriteria criteria)
{
    // sorted by rating: descending order
    if(criteria == BY_RATING){

    }
    // sorted by title
    else if(criteria == BY_TITLE){

    }
}
// Task 2.9: done!
Book *BookList::searchList(int bookId) const
{
    Book* book = nullptr;
    Node* current = this->head;
    while(current != nullptr){
        if (bookId == current->data->getId()){
            book = current->data;
            break;
        }
        current = current->next;
    }
    return book;
}
// Task 2.10: done!
int BookList::countBooks() const
{
    int num_of_book = 0;
    Node* current = this->head;
    while(current != nullptr){
        num_of_book += current->data->getInventoryCount();
        current = current->next;
    }
}
// Task 2.11: done!
void BookList::rateBook(int bookId, double newRating)
{
    searchList(bookId)->addRating(newRating);
}
// Task 2.12: 
Book *BookList::getBookWithMaxRating() const
{

}

Book *BookList::getBookWithMinRating() const
{
}

void BookList::reverseBooksByRating()
{
}