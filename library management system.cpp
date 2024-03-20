#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_SIZE = 100;

class Stack
{
    int top;
    int arr[MAX_SIZE];

public:
    Stack()
    {
        top = -1;
    }

    void push(int element)
    {
        if (top < MAX_SIZE - 1)
        {
            top++;
            arr[top] = element;
        }
        else
        {
            cout << "Stack is full" << endl;
        }
    }

    bool isEmpty()
    {
        return top < 0;
    }

    void pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
        }
        else
        {
            top--;
        }
    }

    int getTop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
            return -1;
        }
        else
        {
            return arr[top];
        }
    }

    void print()
    {
        cout << "[";
        for (int i = top; i > -1; i--)
        {
            cout << arr[i];
            if (i > 0)
            {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
};

class Queue
{
    int arr[MAX_SIZE];
    int front;
    int rear;

public:
    Queue()
    {
        front = -1;
        rear = -1;
    }

    bool isEmpty()
    {
        return (front == -1 && rear == -1);
    }

    void enqueue(int element)
    {
        if (rear != MAX_SIZE - 1)
        {
            if (isEmpty())
            {
                rear++;
                front++;
                arr[rear] = element;
            }
            else
            {
                rear++;
                arr[rear] = element;
            }
        }
        else
        {
            cout << "Queue Full" << endl;
        }
    }

    int dequeue()
    {
        if (!isEmpty() && front <= rear)
        {
            int item = arr[front];
            front++;
            return item;
        }
        else
        {
            cout << "Queue Is Empty" << endl;
            return -1;
        }
    }

    int peek()
    {
        if (!isEmpty() && front <= rear)
        {
            return arr[front];
        }
        else
        {
            cout << "Queue Is Empty" << endl;
            return -1;
        }
    }

    void display()
    {
        if (!isEmpty() && front <= rear)
        {
            for (int i = front; i <= rear; i++)
            {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
        else
        {
            cout << "Queue Is Empty" << endl;
        }
    }
};

class Book
{
public:
    int id;
    string title;
    string author;
    int numCopies;

    Book(int _id, const string &_title, const string &_author, int _numCopies)
    {
        id = _id;
        title = _title;
        author = _author;
        numCopies = _numCopies;
    }
};

class LibraryManagementSystem
{
    Stack bookStack;
    Queue reservationQueue;
    vector<Book> books;

public:
    void line()
    {
        cout << "\n==================================================================================\n\n";
    }
    void addBook()
    {
        int id, numCopies;
        string title, author;

        cout << "Enter Book ID: ";
        cin >> id;
        if (id <= 0)
        {
            cout << "Invalid ID. ID must be a positive integer." << endl;
            line();
            addBook();
        }
        for (const auto &book : books)
        {
            if (book.id == id)
            {
                cout << "Book with ID " << id << " already exists." << endl;
                line();
                addBook();
            }
        }

        cout << "Enter Book Title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);
        cout << "Enter Number of Copies: ";
        cin >> numCopies;

        if (numCopies <= 0)
        {
            cout << "Invalid number of copies. Number of copies must be a positive integer." << endl;
            line();
            addBook();
        }

        Book newBook(id, title, author, numCopies);
        books.push_back(newBook);

        cout << "Book added successfully.\n"
             << endl;
        line();
        return;
    }

    void displayAvailableBooks()
    {
        cout << "                              Available Books:                              ";
        line();
        bool available = false;
        for (const auto &book : books)
        {
            if (book.numCopies > 0)
            {
                cout << "ID:     " << book.id << endl;
                cout << "Title:  " << book.title << endl;
                cout << "Author: " << book.author << endl;
                cout << "Copies: " << book.numCopies << endl;
                line();
                available = true;
            }
        }
        if (!available)
        {
            cout << "No books available." << endl;
            line();
        }
    }

    void borrowBook()
    {
        if (!books.empty())
        {
            int bookId;
            cout << "Enter Book ID to borrow: ";
            cin >> bookId;

            for (auto &book : books)
            {
                if (book.id == bookId && book.numCopies > 0)
                {
                    bookStack.push(bookId);
                    book.numCopies--;
                    cout << "Book with ID " << bookId << " borrowed successfully." << endl;
                    line();
                    return;
                }
            }
            cout << "Book with ID " << bookId << " not available." << endl;
            line();
        }
        else
        {
            cout << "No books available to borrow." << endl;
            line();
        }
    }

    void returnBook()
    {
        if (bookStack.isEmpty())
        {
            cout << "No books have been borrowed yet." << endl;
            line();
            return;
        }

        int choice;
        cout << "Do you want to return the last borrowed book? (1: Yes, 2: No): ";
        cin >> choice;

        if (choice == 1)
        {
            int returnedBook = bookStack.getTop();
            for (auto &book : books)
            {
                if (book.id == returnedBook)
                {
                    bookStack.pop();
                    book.numCopies++;
                    cout << "Book with ID " << returnedBook << " returned successfully." << endl;
                    line();
                    return;
                }
            }
            cout << "Book with ID " << returnedBook << " not found." << endl;
        }
        else if (choice == 2)
        {
            int bookId;
            cout << "Enter Book ID to return: ";
            cin >> bookId;

            bool found = false;
            for (auto &book : books)
            {
                if (book.id == bookId)
                {
                    found = true;
                    if (book.numCopies < 0)
                    {
                        cout << "Book with ID " << bookId << " has not been borrowed." << endl;
                        line();
                        return;
                    }
                    else
                    {
                        book.numCopies++;
                        cout << "Book with ID " << bookId << " returned successfully." << endl;
                        line();
                        return;
                    }
                }
            }

            if (!found)
            {
                cout << "Book with ID " << bookId << " not found." << endl;
                line();
            }
        }
        else
        {
            cout << "Invalid choice." << endl;
            line();
        }
    }

    void reserveBook()
    {
        if (!books.empty())
        {
            int bookId;
            cout << "Enter Book ID to reserve: ";
            cin >> bookId;

            bool bookFound = false;
            for (auto &book : books)
            {
                if (book.id == bookId)
                {
                    bookFound = true;
                    if (book.numCopies == 0)
                    {
                        cout << "All copies of Book with ID " << bookId << " are currently borrowed." << endl;
                        cout << "You can reserve this book to be available when returned." << endl;
                        reservationQueue.enqueue(bookId);
                        cout << "Book with ID " << bookId << " added to the reservation list successfully." << endl;
                        line();
                    }
                    else
                    {
                        cout << "Book with ID " << bookId << " is available. You can borrow it directly." << endl;
                        line();
                    }
                    break;
                }
            }

            if (!bookFound)
            {
                cout << "Book with ID " << bookId << " not found." << endl;

            }
        }
        else
        {
            cout << "No books available to reserve." << endl;
        }
    }

    void processReservedBooks()
    {
        if (!reservationQueue.isEmpty())
        {
            int reservedBookId = reservationQueue.peek();
            bool bookAvailable = false;
            for (auto &book : books)
            {
                if (book.id == reservedBookId && book.numCopies > 0)
                {
                    bookAvailable = true;
                    book.numCopies--;
                    reservationQueue.dequeue();
                    cout << "Reserved book with ID " << reservedBookId << " has been assigned to the next person in the waiting list." << endl;
                    line();
                    break;
                }
            }
            if (!bookAvailable)
            {
                cout << "Reserved book with ID " << reservedBookId << " is still not available." << endl;
                line();
            }
        }
    }

    void displayReservedBooks()
    {
        cout << "Reserved Book id: ";
        reservationQueue.display();

    }
};

int main()
{
    cout << "\t\t\t*--------------------------------------------------------------*\n";
    cout << "\t\t\t|                 Library Management System Menu               |\n";
    cout << "\t\t\t*--------------------------------------------------------------*\n\n\n";
    LibraryManagementSystem library;
    int choice;
    do
    {
        library.line();

        cout << "1. Add Book\n";
        cout << "2. Borrow Book\n";
        cout << "3. Return Book\n";
        cout << "4. Reserve Book\n";
        cout << "5. Process Reserved Books\n";
        cout << "6. Display Available Books\n";
        cout << "7. Display Reserved Books\n";
        cout << "0. Exit\n";
        library.line();
        cout << "Enter your choice: ";
        cin >> choice;
        library.line();

        switch (choice)
        {
        case 1:
            library.addBook();
            break;
        case 2:
            library.borrowBook();
            break;
        case 3:
            library.returnBook();
            break;
        case 4:
            library.reserveBook();
            break;
        case 5:
            library.processReservedBooks();
            break;
        case 6:
            library.displayAvailableBooks();
            break;
        case 7:
            library.displayReservedBooks();
            break;
        case 0:
            cout << R"(
                                                            ,---.
 ,----.                    ,--.    ,--.                     |   |
'  .-./    ,---.  ,---.  ,-|  |    |  |-.,--. ,--.,---.     |  .'
|  | .---.| .-. || .-. |' .-. |    | .-. '\  '  /| .-. :    |  |
'  '--'  |' '-' '' '-' '\ `-' |    | `-' | \   ' \   --.    `--'
 `------'  `---'  `---'  `---'      `---'.-'  /   `----'    .--.
                                         `---'  '--'
)";
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 0);

    return 0;
}
