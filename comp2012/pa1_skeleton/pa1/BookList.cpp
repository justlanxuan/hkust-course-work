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
        int num_of_book = book->getInventoryCount();
        // if inventory count is 1
        if(num_of_book >= 1){// remove the book
            book->changeInventoryCount(-1);
        }
        if(book->getInventoryCount()==0){
            // remove the book
            Node* current = this->head;
            Node* next = current->next;
            while(next != nullptr){
                if(next->data->getId()==book->getId()){
                    current->next = next->next;
                    delete next;
                    return;
                }
                current = next;
                next = next->next;
            } 
        return;
        }
    }
}
// Task 2.7: done!
void BookList::displayBooks() const
{
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
// Task 2.8: maybe done? better sortings?
void BookList::sortBooks(SortCriteria criteria)
{
    int length = 0;
    Node* current = this->head;
    while(current != nullptr){
        length += 1;
        current = current->next;
    }
    if (length == 0 || length == 1){ // no book or one book only, no need to sort
        return;
    }
    else if(criteria == BY_RATING){
        for(int i=0;i<length-1;i++){// iterate on every fixed position
            Node* node1 = this->head;
            Node* node2 = node1->next;
            while(node2!=nullptr){
                if(node1->data->getRating()<node2->data->getRating()){
                    //swap node1 and node 2
                    Book* temp = node1->data;
                    node1->data = node2->data;
                    node2->data = temp;
                }
                node1 = node2;
                node2 = node2->next;
            }
    }
    }
    else if(criteria == BY_TITLE){
        for(int i=0;i<length-1;i++){// iterate on every fixed position
            Node* node1 = this->head;
            Node* node2 = node1->next;
            while(node2!=nullptr){
                if(node1->data->getTitle()>node2->data->getTitle()){
                    //swap node1 and node 2
                    Book* temp = node1->data;
                    node1->data = node2->data;
                    node2->data = temp;
                }
                node1 = node2;
                node2 = node2->next;
            }
    }
    }
    else{
        return;
    }
}
// Task 2.9: done!
Book *BookList::searchList(int bookId) const
{
    Node* current = this->head;
    while(current != nullptr){
        if (bookId == current->data->getId()){
            return current->data;
        }
        current = current->next;
    }
    return nullptr;
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
    return num_of_book;
}
// Task 2.11: done!
void BookList::rateBook(int bookId, double newRating)
{
    if(searchList(bookId) == nullptr){
        cout<<"Book with ID "<<bookId<<" not found."<<endl;
        return;
    }
    searchList(bookId)->addRating(newRating);
    cout<<"Rating updated for Book "<<bookId<<". New rating: "<<searchList(bookId)->getRating()<<endl;
}
// Task 2.12: done!
Book *BookList::getBookWithMaxRating() const
{
    // if the book list is empty
    if(this->isEmpty()){
        cout<<"The book list is empty."<<endl;
        return nullptr;
    }
    else{
        Book* max_rating_book = this->head->data;
        Node* current = this->head;
        while(current != nullptr){
            // compare
            if(current->data->getRating()>max_rating_book->getRating()){
                max_rating_book = current->data;
            }
            current = current->next;
        }
        return max_rating_book;
    }
}
// Task 2.13: done!
Book *BookList::getBookWithMinRating() const
{
    // if the book list is empty
    if(this->isEmpty()){
        cout<<"The book list is empty."<<endl;
        return nullptr;
    }
    else{
        Book* min_rating_book = this->head->data;
        Node* current = this->head;
        while(current != nullptr){
            // compare
            if(current->data->getRating()<min_rating_book->getRating()){
                min_rating_book = current->data;
            }
            current = current->next;
        }
        return min_rating_book;
    }
}
// Task 2.14: reverse the list or output as ascending order?
void BookList::reverseBooksByRating()
{
    if(this->head == nullptr){
        return;
    }
    this->sortBooks(BY_RATING); // in descending order
    // reverse the linked list
    Node* current = this->head;
    Node* next = this->head->next;
    while(next != nullptr){
        Node* temp_next_next = next->next;
        next->next = current;
        current = next;
        next = temp_next_next;        
    }
    this->head->next = nullptr;
    this->head = current;
    return;
}