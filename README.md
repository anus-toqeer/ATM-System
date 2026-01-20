I developed a C++-based ATM Management System that simulates the core functionalities of an actual ATM. The project focuses on file handling, control structures, data validation, and user interaction.
🧩 Key Features:
🔑 PIN Authentication:
Secure login with a 3-attempt PIN validation system
PIN changes are saved and loaded from external files
💳 Card Type Selection:
Supports Silver, Gold, and Platinum cards with tier-based transaction limits
💵 Functional Modules:
Balance Inquiry – Display current balance
Cash Withdrawal – Limited by balance & card type
Cash Deposit – Validated by card’s maximum deposit cap
Funds Transfer – Secure money transfer with validation
PIN Change – Old PIN verification and new PIN confirmation
💾 Persistent Data Handling:
Uses file I/O to store and retrieve PIN and balance across sessions
🚫 Input Validation:
Ensures negative or invalid inputs are gracefully handled
Prevents overdrawing or exceeding ATM cash capacity
👨‍💻 Technologies Used:
Language: C++
Concepts: File Handling, Loops, Conditions, Modular Programming
✅ This project demonstrates practical implementation of real-world banking operations using fundamental C++ principles.
