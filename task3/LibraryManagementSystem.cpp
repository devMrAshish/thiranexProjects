/*
=====================================================================
 Library Management System
=====================================================================
 Description:
   A console-based Library Management System written in C++ using
   Object-Oriented Programming (classes). It manages:
     - Books        (add, search by title/author, list)
     - Members      (add, list)
     - Borrowing    (issue a book, return a book)

 Key Features implemented (as required):
   1. Classes for Book and Member details.
   2. Book issue and return functionality.
   3. Search functionality by title or author.

 Author : (generated for Library Management System task)
=====================================================================
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

// ---------------------------------------------------------------------------
// Utility: case-insensitive substring search
// ---------------------------------------------------------------------------
string toLower(const string& s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(),
              [](unsigned char c) { return tolower(c); });
    return result;
}

bool containsIgnoreCase(const string& haystack, const string& needle) {
    return toLower(haystack).find(toLower(needle)) != string::npos;
}

// ---------------------------------------------------------------------------
// Class: Book
// Stores details of a single book in the library.
// ---------------------------------------------------------------------------
class Book {
public:
    int id;
    string title;
    string author;
    int totalCopies;
    int availableCopies;

    Book() : id(0), totalCopies(0), availableCopies(0) {}

    Book(int id, const string& title, const string& author, int copies)
        : id(id), title(title), author(author),
          totalCopies(copies), availableCopies(copies) {}

    void display() const {
        cout << left
             << "ID: " << setWidth(id, 4)
             << " | Title: " << setWidthStr(title, 25)
             << " | Author: " << setWidthStr(author, 20)
             << " | Available: " << availableCopies
             << "/" << totalCopies
             << '\n';
    }

private:
    // small helpers to keep columns tidy without pulling in <iomanip> noise
    static string setWidth(int value, int width) {
        string s = to_string(value);
        while ((int)s.size() < width) s += ' ';
        return s;
    }
    static string setWidthStr(const string& value, int width) {
        string s = value;
        if ((int)s.size() > width) s = s.substr(0, width - 3) + "...";
        while ((int)s.size() < width) s += ' ';
        return s;
    }
};

// ---------------------------------------------------------------------------
// Class: Member
// Stores details of a single library member.
// ---------------------------------------------------------------------------
class Member {
public:
    int id;
    string name;
    string contact;
    vector<int> borrowedBookIds; // book IDs currently borrowed by this member

    Member() : id(0) {}

    Member(int id, const string& name, const string& contact)
        : id(id), name(name), contact(contact) {}

    void display() const {
        cout << "ID: " << id
             << " | Name: " << name
             << " | Contact: " << contact
             << " | Books Borrowed: " << borrowedBookIds.size()
             << '\n';
    }
};

// ---------------------------------------------------------------------------
// Class: Library
// Manages collections of Books and Members, and handles issue/return
// and search operations. This is the "controller" class of the system.
// ---------------------------------------------------------------------------
class Library {
private:
    vector<Book> books;
    vector<Member> members;
    int nextBookId;
    int nextMemberId;

    // Find a book by its ID; returns pointer or nullptr if not found.
    Book* findBookById(int id) {
        for (auto& b : books)
            if (b.id == id) return &b;
        return nullptr;
    }

    // Find a member by their ID; returns pointer or nullptr if not found.
    Member* findMemberById(int id) {
        for (auto& m : members)
            if (m.id == id) return &m;
        return nullptr;
    }

public:
    Library() : nextBookId(1), nextMemberId(1) {}

    // --------------------------- Book management ---------------------------
    void addBook(const string& title, const string& author, int copies) {
        books.emplace_back(nextBookId++, title, author, copies);
        cout << ">> Book added successfully.\n";
    }

    void listBooks() const {
        if (books.empty()) {
            cout << "No books in the library yet.\n";
            return;
        }
        cout << "\n--- Book Catalogue ---\n";
        for (const auto& b : books) b.display();
    }

    // Search by title OR author (partial, case-insensitive match)
    void searchBooks(const string& keyword) const {
        bool found = false;
        cout << "\n--- Search Results for \"" << keyword << "\" ---\n";
        for (const auto& b : books) {
            if (containsIgnoreCase(b.title, keyword) ||
                containsIgnoreCase(b.author, keyword)) {
                b.display();
                found = true;
            }
        }
        if (!found) cout << "No matching books found.\n";
    }

    // --------------------------- Member management --------------------------
    void addMember(const string& name, const string& contact) {
        members.emplace_back(nextMemberId++, name, contact);
        cout << ">> Member registered successfully.\n";
    }

    void listMembers() const {
        if (members.empty()) {
            cout << "No members registered yet.\n";
            return;
        }
        cout << "\n--- Registered Members ---\n";
        for (const auto& m : members) m.display();
    }

    // --------------------------- Issue / Return -----------------------------
    void issueBook(int bookId, int memberId) {
        Book* book = findBookById(bookId);
        Member* member = findMemberById(memberId);

        if (!book) {
            cout << "Error: Book ID not found.\n";
            return;
        }
        if (!member) {
            cout << "Error: Member ID not found.\n";
            return;
        }
        if (book->availableCopies <= 0) {
            cout << "Error: \"" << book->title << "\" is currently unavailable.\n";
            return;
        }

        book->availableCopies--;
        member->borrowedBookIds.push_back(bookId);
        cout << ">> Book \"" << book->title << "\" issued to "
             << member->name << ".\n";
    }

    void returnBook(int bookId, int memberId) {
        Book* book = findBookById(bookId);
        Member* member = findMemberById(memberId);

        if (!book) {
            cout << "Error: Book ID not found.\n";
            return;
        }
        if (!member) {
            cout << "Error: Member ID not found.\n";
            return;
        }

        auto it = find(member->borrowedBookIds.begin(),
                        member->borrowedBookIds.end(), bookId);

        if (it == member->borrowedBookIds.end()) {
            cout << "Error: This member did not borrow that book.\n";
            return;
        }

        member->borrowedBookIds.erase(it);
        book->availableCopies++;
        cout << ">> Book \"" << book->title << "\" returned by "
             << member->name << ".\n";
    }

    // Pre-loads a few sample records so the program is usable immediately.
    void loadSampleData() {
        addBook("The C++ Programming Language", "Bjarne Stroustrup", 3);
        addBook("Clean Code", "Robert C. Martin", 2);
        addBook("Design Patterns", "Erich Gamma", 1);
        addMember("Aarav Sharma", "aarav@example.com");
        addMember("Riya Patel", "riya@example.com");
    }
};

// ---------------------------------------------------------------------------
// Helper input functions (basic validation for a console app)
// ---------------------------------------------------------------------------
int readInt(const string& prompt) {
    int value;
    cout << prompt;
    while (!(cin >> value)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

string readLine(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

// ---------------------------------------------------------------------------
// Menu / Main program
// ---------------------------------------------------------------------------
void printMenu() {
    cout << "\n===================================\n";
    cout << "   LIBRARY MANAGEMENT SYSTEM\n";
    cout << "===================================\n";
    cout << " 1. Add Book\n";
    cout << " 2. Add Member\n";
    cout << " 3. Issue Book\n";
    cout << " 4. Return Book\n";
    cout << " 5. Search Book (title or author)\n";
    cout << " 6. List All Books\n";
    cout << " 7. List All Members\n";
    cout << " 0. Exit\n";
    cout << "===================================\n";
}

int main() {
    Library library;

    int choice;
    do {
        printMenu();
        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1: {
                string title = readLine("Enter book title: ");
                string author = readLine("Enter book author: ");
                int copies = readInt("Enter number of copies: ");
                library.addBook(title, author, copies);
                break;
            }
            case 2: {
                string name = readLine("Enter member name: ");
                string contact = readLine("Enter member contact (email/phone): ");
                library.addMember(name, contact);
                break;
            }
            case 3: {
                int bookId = readInt("Enter Book ID to issue: ");
                int memberId = readInt("Enter Member ID: ");
                library.issueBook(bookId, memberId);
                break;
            }
            case 4: {
                int bookId = readInt("Enter Book ID to return: ");
                int memberId = readInt("Enter Member ID: ");
                library.returnBook(bookId, memberId);
                break;
            }
            case 5: {
                string keyword = readLine("Enter title or author keyword: ");
                library.searchBooks(keyword);
                break;
            }
            case 6:
                library.listBooks();
                break;
            case 7:
                library.listMembers();
                break;
            case 0:
                cout << "Exiting Library Management System. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
