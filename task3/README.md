# Library Management System (C++)

A simple console-based **Library Management System** written in C++ using
Object-Oriented Programming. It manages books, members, and borrowing
records, and meets the following requirements:

- Structures/classes for book and member details
- Book issue and return functionality
- Search functionality by title or author

---

## File

| File | Description |
|---|---|
| `LibraryManagementSystem.cpp` | Single-file C++ source containing the entire program |

---

## How It Works

### Classes

**`Book`**
Holds the details of one book:
- `id` — unique auto-generated identifier
- `title`, `author`
- `totalCopies` — how many copies the library owns
- `availableCopies` — how many copies are currently on the shelf (not borrowed)

**`Member`**
Holds the details of one library member:
- `id` — unique auto-generated identifier
- `name`, `contact`
- `borrowedBookIds` — list of book IDs the member currently has checked out

**`Library`**
The "controller" class. It owns the list of all books and members and
exposes all the operations:
- `addBook()`, `listBooks()`, `searchBooks()`
- `addMember()`, `listMembers()`
- `issueBook()`, `returnBook()`

Keeping data (`Book`, `Member`) separate from behavior (`Library`) keeps the
code organized and easy to extend.

### Issue / Return Logic

- **Issuing** a book checks that the book exists, the member exists, and
  there is at least one available copy. If all checks pass, it decreases
  `availableCopies` by 1 and adds the book's ID to the member's
  `borrowedBookIds` list.
- **Returning** a book checks that the member actually has that book
  borrowed. If so, it removes the ID from `borrowedBookIds` and increases
  `availableCopies` back by 1.

This prevents issuing a book that has no copies left, and prevents
"returning" a book a member never borrowed.

### Search

`searchBooks(keyword)` scans every book and matches the keyword against
**both** the title and the author, case-insensitively, using a partial
(substring) match. For example, searching `"clean"` will find *Clean Code*,
and searching `"martin"` will also find it (by author).

### Sample Data

When the program starts, `loadSampleData()` automatically adds 3 sample
books and 2 sample members so you can try every menu option immediately
without typing data in first. Remove the call to `loadSampleData()` in
`main()` if you'd prefer to start with an empty library.

---

## How to Compile and Run

You need a C++ compiler that supports C++11 or later (C++17 recommended).

### Linux / macOS (g++)
```bash
g++ -std=c++17 -Wall -o lms LibraryManagementSystem.cpp
./lms
```

### Windows (MinGW / g++)
```bash
g++ -std=c++17 -Wall -o lms.exe LibraryManagementSystem.cpp
lms.exe
```

### Windows (Visual Studio)
1. Create a new "Console App" project.
2. Replace the generated `.cpp` file's contents with
   `LibraryManagementSystem.cpp`.
3. Build and Run (Ctrl+F5).

---

## Using the Program

After running it, you'll see a menu:

```
===================================
   LIBRARY MANAGEMENT SYSTEM
===================================
 1. Add Book
 2. Add Member
 3. Issue Book
 4. Return Book
 5. Search Book (title or author)
 6. List All Books
 7. List All Members
 0. Exit
===================================
Enter your choice:
```

Type the number of the action you want and follow the prompts.

| Option | What it does |
|---|---|
| 1 | Add a new book (title, author, number of copies) |
| 2 | Register a new member (name, contact) |
| 3 | Issue a book — enter the Book ID and the Member ID |
| 4 | Return a book — enter the Book ID and the Member ID |
| 5 | Search by keyword — matches against title or author |
| 6 | Show every book in the catalogue with availability |
| 7 | Show every registered member and how many books they hold |
| 0 | Exit the program |

> **Tip:** Book IDs and Member IDs are assigned automatically (starting at
> 1) in the order you add them, and are shown whenever you list books/members.

---

## Notes / Possible Extensions

This is an in-memory program — data resets each time you close it. Ideas
for extending it further:
- Save/load data to a file (CSV or simple text) so records persist between runs
- Add due dates and overdue-fine calculation
- Add book deletion / member removal
- Add a graphical or web front-end on top of the same `Library` class
