# 🚆 Railway Reservation Management System

A menu-driven Railway Reservation Management System developed using **C Programming Language** as part of the **Data Structures (CSE2253) Mini Project**.

## 📌 Project Overview

The Railway Reservation Management System is a console-based application designed to simulate basic railway ticket reservation operations.

It allows users to view available trains, book tickets, cancel reservations, search for booking details, and manage a waiting list.

The project demonstrates the practical implementation of fundamental Data Structures concepts using C.

## 🎯 Objectives

- To implement a simple railway reservation system using C.
- To understand and apply different data structures.
- To manage passenger reservation records efficiently.
- To implement ticket booking and cancellation operations.
- To maintain a waiting list using the FIFO principle.

## ✨ Features

1. **View Available Trains** – Display train details, routes, and available seats.
2. **Book Tickets** – Reserve a seat by entering passenger details.
3. **Cancel Tickets** – Cancel confirmed or waiting-list reservations.
4. **View All Reservations** – Display all active booking records.
5. **Search Reservation** – Find booking details using a unique booking ID.
6. **Waiting List Management** – Add passengers to a waiting list when seats are unavailable.
7. **Automatic Seat Allocation** – Assign a released seat to the first eligible waiting passenger after cancellation.

## 🧠 Data Structures Used

| Data Structure | Application |
|---|---|
| Arrays | Store train details and seat availability |
| Structures | Organize train and passenger information |
| Linked Lists | Maintain passenger reservation records |
| Queues | Manage waiting-list passengers using FIFO |

## 🛠️ Technologies Used

- **Programming Language:** C
- **Compiler:** GCC
- **IDE:** Visual Studio Code
- **Version Control:** Git and GitHub

## 📂 Project Structure

```text
railway-reservation-management-system/
│
├── railway_reservation.c
├── Railway_Reservation_Project_Report.docx
├── README.md
└── .gitignore
```

## ⚙️ Installation and Execution

### Prerequisites

- GCC compiler
- Git
- Visual Studio Code (optional)

### Step 1: Clone the Repository

```bash
git clone https://github.com/YOUR-USERNAME/railway-reservation-management-system.git
```

### Step 2: Navigate to the Project Directory

```bash
cd railway-reservation-management-system
```

### Step 3: Compile the Program

```bash
gcc -std=c99 -Wall -Wextra railway_reservation.c -o railway
```

### Step 4: Run the Program

```bash
./railway
```

## 📋 Main Menu

```text
===============================================
       RAILWAY RESERVATION MANAGEMENT SYSTEM
===============================================

1. View Available Trains
2. Book Ticket
3. Cancel Ticket
4. View All Reservations
5. Search Reservation
6. View Waiting List
7. Exit

Enter your choice:
```

## 🚉 System Functionality

- The system contains five predefined trains.
- Each train has a maximum capacity of ten seats.
- Every booking receives a unique booking ID during program execution.
- If seats are available, the passenger receives a confirmed reservation.
- If all seats are occupied, the passenger is added to the waiting list.
- When a confirmed ticket is cancelled, the first eligible waiting passenger for that train receives the available seat.

## ⚠️ Limitations

- Train details are predefined.
- The system supports a limited number of trains and seats.
- Reservation records are stored temporarily in memory.
- Data is not retained after the program terminates.
- This is an educational simulation and is not connected to a real railway reservation service.

## 🚀 Future Enhancements

- Implement file handling for permanent data storage.
- Add functionality to add and modify train details.
- Introduce different coach and seat categories.
- Implement date-wise reservations.
- Integrate a database for passenger records.


## 🎓 Academic Information

- **Project:** Railway Reservation Management System
- **Subject:** Data Structures
- **Course Code:** CSE2253
- **Institution:** Presidency School of Computer Science and Engineering
- **Academic Year:** 2026–2027

## 📄 License

This project is developed for academic and educational purposes as part of the Data Structures mini project.

---

**Made with C | Data Structures Mini Project 2026**
