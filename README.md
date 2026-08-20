# CLI-ATM-Banking-Simulator-in-C
A feature-packed Command Line ATM &amp; Core Banking Simulator built in C featuring anti-fraud verification, cash denomination dispensing, micro-loans, utility bill payments, and financial health analytics.


#  Advanced ATM & Core Banking Simulator in C

A comprehensive, interactive Command-Line Interface (CLI) ATM application built using Pure C. This project simulates real-world core banking logic, hardware constraints (cash denomination dispenser), security layers (anti-fraud & OTPs), and financial analytics.

##  Features:

###  Security & Anti-Fraud
* **5-Digit Authentication & Account Locking:** Automatically locks account access after 3 consecutive failed login attempts.
* **Admin Override Mode:** Dedicated administrative interface (PIN: `99999`) to inspect system vault levels and unlock accounts.
* **Anti-Fraud Security Engine:** Flags high-value withdrawals (>80% of current balance) and mandates two-step re-verification (Dynamic Security Code + PIN check).
* **OTP Verification:** Dynamic 4-digit OTP generation for sensitive operations like changing PINs or opening Fixed Deposits.

###  Cash Hardware & Banking Logic
* **Smart Denomination Dispenser:** Uses a greedy algorithm (`/` and `%` arithmetic) to dispense exact bill counts for **Rs. 500**, **Rs. 200**, and **Rs. 100** notes.
* **Minimum Balance Constraint:** Enforces account safety thresholds (e.g., maintaining minimum Rs. 10,000 balance).
* **Daily Withdrawal Limit:** Tracks accumulated daily spending against configurable daily caps.

###  Utility & Financial Products
* **Utility Bill Payments:** Instant balance deduction for Electricity, Internet, Mobile Postpaid, and Gas bills.
* **Fixed Deposit (FD) Creator:** Calculates annual maturity returns at a standard 6.5% p.a. interest rate.
* **Emergency Micro-Loan (Cash Advance):** Grants instant emergency liquidity (up to Rs. 7,500) when account reserves are low, with active debt tracking.
* **Loan Repayment Option:** Integrated feature to pay back active micro-loan debts.
* **Account Health & Risk Rating:** Analyzes account parameters in real-time to generate a dynamic **0–100 Financial Health Score** with risk status levels.
* **Savings Interest Preview:** Previews compound projection over 1-year, 3-year, and 5-year periods.
* **Last Transaction Tracker:** Retains transaction metadata (type, amount, updated balance) for instant audit retrieval

##  Concepts Used
- Basic Data Types: int, float, and char.
- Input and Output: scanf and printf with format specifiers.
- Conditional Logic: if, else if, and switch-case statements.
- Iteration: while and for loops.
- Standard Libraries: stdlib.h for random number generation and time.h for seeding.
- Math Operations: Modulo (%) and integer division (/) for currency calculations.


message me if any bugs found.
