🍽️ Restaurant Billing System
📌 Overview
This is a simple restaurant billing system implemented in C language.
It simulates a basic billing process for a restaurant, allowing users to generate, save, and search customer invoices.

✨ Features & Functionality
✅ Generate Invoice

Enter customer name and date.

Choose from a predefined list of 5 menu items.

Enter item quantities.

Automatically applies:

🔟 10% Discount

💸 9% CGST + 9% SGST

Displays full bill breakdown.

Saves invoice to invoices.txt.

✅ Show All Invoices

Displays all saved invoices from invoices.txt.

✅ Search Invoice

Search invoices by customer name.

✅ Exit Option

Gracefully exits the program.

🛠️ Technologies Used
C Programming Language

GCC Compiler

Text Files for Data Storage

CLI (Command Line Interface)

🚀 How It Works
Launch the program.

The main menu provides 4 options:

Generate Invoice

Show All Invoices

Search Invoice

Exit

When generating an invoice:

Enter customer name and date.

Select items and their quantities from the predefined menu.

Program calculates subtotal, taxes, discount, and grand total.

Displays formatted bill and saves it to a file.

Invoices are stored and retrieved from invoices.txt.

📌 Code Structure
1️⃣ Menu Items:

Hardcoded list of 5 food items with prices.

2️⃣ Invoice Generation:

Calculates total, discount, taxes, and grand total.

Displays detailed bill format.

Saves bill details in invoices.txt.

3️⃣ File Handling:

Stores and reads invoice records from a text file.

Enables search and display of customer invoices.

4️⃣ Main Menu Navigation:

Provides options to perform all core functionalities.

🖥️ Installation
🔹 Prerequisites:
Ensure you have a C compiler like GCC installed on your system.

🚀 How to Run the Program
🔹 Compilation:
sh
Copy
Edit
gcc billing_system.c
🔹 Execution:
sh
Copy
Edit
./a.out
🔹 Menu Options:
Generate Invoice

Show All Invoices

Search Invoice

Exit

🎯 Future Improvements
📌 Allow dynamic item list (instead of hardcoding 5 items).

📌 Add features to update or delete invoices.

📌 Implement login functionality for admin and staff.

📌 Improve file format (CSV/JSON) for better readability and data handling.
