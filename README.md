# 🍽️ Restaurant Billing System

## 📌 Overview
The **Restaurant Billing System** is a simple billing simulation project written in C.  
It allows users to generate, store, and search invoices based on customer orders.

## ✨ Features

### 1. Generate Invoices
- User-friendly menu display with 5 predefined items
- Input customer name, date, item selections, and quantities
- Applies:
  - 🔟 **10% Discount**
  - 💸 **9% CGST + 9% SGST**
- Displays a full bill breakdown (subtotal, taxes, discount, grand total)
- Stores invoice data in `invoices.txt`

### 2. Show All Invoices
- Reads and displays all saved invoices from the file

### 3. Search Invoice by Customer Name
- Searches and displays invoice records for a given customer

---

## 🛠️ Technologies Used
- **C Language** – Core programming logic
- **GCC Compiler** – For compiling and running the program
- **Text Files** – For persistent invoice data storage
- **CLI** – Console-based user interface

---

## ⚙️ How It Works

### 1. Main Menu Options:

1. Generate Invoice

2. Show All Invoices

3. Search Invoice

4. Exit


### 2. Generate Invoice:
- Enter customer name and date
- View menu and select items with quantities
- Calculates:
  - Subtotal
  - 10% Discount
  - 9% CGST + 9% SGST
  - Grand Total
- Prints formatted invoice
- Saves invoice to `invoices.txt`

### 3. Show All Invoices:
- Reads from `invoices.txt` and displays all stored bills

### 4. Search Invoice:
- User enters customer name
- Displays all matching invoices found in the file

### 5. Exit:
- Terminates the program

---

## 🚀 How to Run the Program

### 🔹 Clone or Download the Repository  
git clone https://github.com/Vaishnavi-2401/Restaurant_Billing_System.git

### 🔹 Compile the Code
gcc billing_system.c -o billing_system

### 🔹 Run the Program
./billing_system

## 🎯 Future Improvements
🔧 Add support for dynamic item lists instead of hardcoded items

🗑️ Include features to delete or update existing invoices

🔐 Implement login functionality for admin and staff roles
