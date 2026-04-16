# Movie Ticket Booking System (Data Structures & Algorithms)

This project is a comprehensive C++ application designed to manage cinema bookings. It demonstrates the practical application of multiple data structures to handle scheduling, seating arrangements, and customer priority.

## 🚀 Key Features
- **Show Scheduling:** Uses a **Linked List** structure to manage different show timings (Afternoon and Evening).
- **Interactive Seating Map:** A **2D Array** implementation that tracks 30 unique seats with different categories (VIP vs. Regular).
- **Automated Waitlist:** Integrated **Queue (FIFO)** system that automatically assigns cancelled seats to the next person in line.
- **Dynamic Reporting:** Real-time generation of booking statistics, including occupancy rates and waitlist size.

## 🧠 Data Structures Used
- **Linked List (Show Nodes):** Each node represents a movie show, allowing the system to scale and add more showtimes easily.
- **2D Array (Matrix):** Represents the physical layout of the theater ($5 \times 6$ grid), enabling $O(1)$ access time for seat booking and verification.
- **Queue (Waitlist):** Ensures a fair "First-Come, First-Served" logic for users waiting for a seat to become available.
- **Structs:** Custom data types used to bundle seat attributes (name, category, booking status) for cleaner code organization.

## 🛠️ Technical Stack
- **Language:** C++
- **Libraries:** `iostream`, `iomanip`, `queue`, `string`
- **Concepts:** Pointer Manipulation, Memory Management, Matrix Traversals, Queue Operations.

## 📂 Project Structure
- `main.cpp`: Contains the core logic for the Booking System, including the ShowNode graph and seat management procedures.

## ⚙️ How to Run
1. Compile the code using any standard C++ compiler:
   ```bash
   g++ main.cpp -o booking_system
