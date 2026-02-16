# Colossus Airlines Reservation System

## Problem Statement
In the previous version of the Colossus Airlines reservation system, any reservation data would be lost when the program closed.  
The goal of this project was to make the system **save reservation data in a file** so that when the program starts again, previous reservations are still there.

---

## How I Solved It
- I used a `struct` for each seat to store the seat ID, first name, last name, and whether it’s taken.  
- I added **file saving and loading** so that outbound and inbound flights each have their own `.dat` file.  
- The program menu lets you:  
  1. See how many seats are empty  
  2. List empty seats  
  3. Show a list of assigned seats alphabetically by last name  
  4. Assign a seat  
  5. Delete a seat assignment  
  6. Go back to the main menu  
- Whenever a seat is assigned or removed, the program **updates the file automatically**, so data is never lost.

---

## Pros and Cons

**Pros:**
- Reservation data is saved between runs.  
- Menu is easy to use.  
- Seat info is stored in a simple struct (like an ADT).  

**Cons:**
- Max 24 seats per flight.  
- Only checks if a seat is taken, no extra validation.  
- Files are binary, so you can’t read them outside the p
