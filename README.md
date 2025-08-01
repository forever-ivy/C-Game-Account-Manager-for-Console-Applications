# 🎮 Game Account Management System

A comprehensive C++-based game account management system that provides user registration, login, equipment management, and security monitoring features.

## ✨ Features

### 👤 User Functions

- **Account Registration & Login** - Supports new user registration and existing user login.
- **Password Security** - Uses MD5 encryption to store user passwords.
- **Equipment System** - View and purchase in-game equipment.
- **User Profile** - Automatically creates a dedicated data file for each user.
- **Initial Funds** - New users receive 5000 game coins upon registration.

### 🛡️ Administrator Functions

- **Security Monitoring** - Monitor login attempts and unusual activities.
- **Account Management** - Handle rule-violating accounts and security incidents.
- **Log Auditing** - Review system security logs.

### 🔒 Security Module

- **Login Monitoring** - Records all login attempts.
- **Account Locking** - Automatically locks suspicious accounts.
- **Security Logs** - Detailed records of security-related events.
- **Violation Handling** - Administrators can manage accounts that violate rules.

## 🛠️ Tech Stack

- **Core Language**: C++
- **Programming Paradigm**: Object-Oriented Programming (OOP), including inheritance and polymorphism.
- **Data Persistence**: File I/O operations (`.txt`, `.csv`).
- **Security**: MD5 hash algorithm for password encryption.
- **Platform-Specific APIs**: Windows API (`<Windows.h>`, `<direct.h>`).
- **Development Environment**: Visual Studio.

## 🏗️ Project Structure

```
GameAccountManagement/
├── Account.h              # Base class definition for accounts
├── Gamer.h/.cpp          # Gamer user class
├── Administrador.h/.cpp   # Administrator class
├── SecurityModule.h/.cpp  # Security module
├── md5.h/.cpp            # MD5 encryption implementation
├── globalFile.h          # Global file path definitions
├── main.cpp              # Main program entry point
├── user_data/            # Directory for user data
├── accountsdat.txt       # Account data file
├── equipment.txt         # Equipment data file
├── login_logcsv.txt      # Login log
├── securitylog.txt       # Security log
└── locked.txt            # List of locked accounts
```

## 🚀 Quick Start

### Prerequisites

- **Compiler**: Visual Studio 2019+ or a C++11 compatible compiler.
- **Operating System**: Windows (uses Windows-specific APIs).
- **Dependencies**: Standard C++ Library.

### Compilation and Execution

1.  **Clone the project**

    ```bash
    git clone <repository-url>
    cd GameAccountManagement
    ```

2.  **Compile with Visual Studio**

    - Open `GameAccountManagement.sln`.
    - Select Debug or Release configuration.
    - Press F5 to run or Ctrl+F5 to compile and run.

3.  **Compile from the command line**
    ```bash
    # Using the MSVC compiler
    cl /EHsc main.cpp Gamer.cpp Administrador.cpp SecurityModule.cpp md5.cpp
    ```

## 📖 Usage

### Starting the Program

After running the program, you will see the main menu:

```
======================  Welcome to the Game Account Management System  =====================

Please select your operation
        -------------------------------
        |                               |
        |          1. User Login        |
        |                               |
        |          2. Admin Login       |
        |                               |
        |          3. Exit System       |
        |                               |
        -------------------------------
```

### User Workflow

1.  **Select User Login** (Option 1).
2.  **Enter username and password**.
3.  **For first-time users, choose to register** (Y/N).
4.  **After successful login, you can**:
    - View equipment
    - Purchase equipment
    - Log out

### Administrator Workflow

1.  **Select Admin Login** (Option 2).
2.  **Enter administrator credentials**.
3.  **Administrator functions**:
    - Check login attempt records.
    - Handle rule-violating accounts.

## 📁 Data Files Description

| Filename           | Purpose                         | Format                             |
| ------------------ | ------------------------------- | ---------------------------------- |
| `accountsdat.txt`  | Stores user account information | `username password_hash role_type` |
| `login_logcsv.txt` | Successful login log            | `username login_time`              |
| `securitylog.txt`  | Security event log              | `username event_time`              |
| `equipment.txt`    | Equipment store data            | List of equipment                  |
| `locked.txt`       | Locked accounts                 | List of locked accounts            |
| `user_data/*.txt`  | Individual user data            | Username, money, equipment, etc.   |

## 🛠️ Development Notes

### Class Hierarchy

```
Account (Abstract Base Class)
├── Gamer
└── Administrador

SecurityModule
```

### Main Design Patterns

- **Inheritance and Polymorphism** - `Account` base class with `Gamer` and `Administrador` derived classes.
- **Composition** - `SecurityModule` as a separate component.
- **File Management** - Centralized management of file paths.



## 📄 License

This project is for learning and research purposes only.

