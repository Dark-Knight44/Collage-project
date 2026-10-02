# PG Management System

A console-based PG (Paying Guest) Management System developed in C. The project is designed to manage student records, room allocation, rent details, payment status, and lunch records.

The project uses binary files to store data so that the records remain available when the program is run again.

## Features

### Student Management

* Add new students
* Generate student IDs
* Assign students to rooms
* Remove students
* Search students using Student ID
* View active students
* View previous students
* Store student details such as name, phone number, course, room number, joining date, and payment status

### Room Management

* View available rooms
* View room occupancy
* Assign students to rooms
* Shift students between rooms
* Lock and unlock rooms
* Prevent allocation when a room is full or locked
* Each room can accommodate up to 3 students

### Payment and Rent Management

* Store student payment information
* Update payment status
* Check pending payments
* Maintain rent records

### Lunch Management

* Store and manage lunch-related records
* Maintain lunch information separately from student and room records

## Data Storage

The program uses binary files for storing records.

| File           | Description                     |
| -------------- | ------------------------------- |
| `students.dat` | Stores student records          |
| `rooms.dat`    | Stores room information         |
| `rent.dat`     | Stores rent and payment records |
| `lunch.dat`    | Stores lunch-related records    |

## Technologies Used

* C
* Structures
* Functions
* Pointers
* Arrays
* File Handling
* Binary File I/O

## Project Structure

```text
Collage-project/
│
├── PG_manager.c
├── PG_manager/
├── students.dat
├── rooms.dat
├── rent.dat
├── lunch.dat
├── clg project.zip
└── README.md
```

## Requirements

To compile and run the project, you need:

* GCC compiler
* Linux/macOS terminal or another environment that supports the required C functions

## How to Run

Clone the repository:

```bash
git clone https://github.com/Dark-Knight44/Collage-project.git
```

Go to the project directory:

```bash
cd Collage-project
```

Compile the program:

```bash
gcc PG_manager.c -o PG_manager
```

Run the program:

```bash
./PG_manager
```

## Room Allocation

When a student is added, the program searches for a room with available space and assigns the student to it.

Each room can have a maximum of three students.

Example:

```text
Room 1
Student 1
Student 2
Student 3

Room 2
Student 4
Student 5

Room 3
Empty
```

Locked rooms are not considered for new student allocation.

## Concepts Used

The project demonstrates the use of basic and intermediate C programming concepts, including:

* Structures
* Nested structures
* Functions
* Pointers
* Arrays
* Loops
* Conditional statements
* File handling
* Binary file operations
* Searching and updating records
* Menu-driven programming

## Future Improvements

Some possible improvements for the project are:

* Add a graphical user interface
* Use MySQL or another database instead of binary files
* Add administrator login
* Add password protection
* Generate rent receipts
* Add automatic monthly billing
* Add better input validation
* Add backup and restore functionality
* Improve Windows compatibility

## Author

Dark-Knight44

GitHub: https://github.com/Dark-Knight44/Collage-project

## License

This project was created for educational purposes.
