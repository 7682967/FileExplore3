# 🌟 File Explorer Application (Linux OS Project)

### 🧾 Overview
The **File Explorer Application** is a console-based project developed in **C++** that allows users to perform fundamental **file and directory management** operations within a **Linux operating system**.  
It simulates the core functionalities of a GUI-based file manager — directly from the terminal.

---

### 🎯 Objective
To design and implement a **console-based File Explorer** that:
- Lists files and directories.
- Allows directory navigation.
- Enables file operations like **create, delete, rename, and copy**.
- Supports **search functionality** and **permission management** using Linux system calls.

---

### ⚙️ Features
- 📂 **List Files:** Display files and directories (recursively).  
- 📁 **Navigate Directories:** Move between different folders easily.  
- ✏️ **File Operations:** Create, delete, rename, or copy files.  
- 🔍 **Search Feature:** Find files anywhere in the directory structure.  
- 🔐 **Permission Handling:** View and modify file permissions.  
- 🧾 **Activity Logging:** Tracks key file operations in a log file.  
- 🎨 **Colored UI:** Clean, terminal-friendly interface using ANSI colors.

---

### 🏗️ Project Structure
FileExplorer3/
│
├── file_explorer3.cpp # Main C++ source code
├── file_explorer.log # Log file (auto-generated)
├── README.md # Project documentation
└── screenshots/ # (Optional) Program output images

---

### 🧠 Technologies Used
- **Language:** C++17  
- **Libraries:** `<dirent.h>`, `<unistd.h>`, `<sys/stat.h>`, `<fstream>`, `<ctime>`  
- **Platform:** Linux (Ubuntu / WSL)  

---

### 🧩 How to Run the Program

1. **Clone the Repository**
   ```bash
   git clone https://github.com/7682926290/FileExplorer3.git
   cd FileExplorer3
 ### Compile the Code
g++ file_explorer3.cpp -o file_explorer3 -std=c++17 -Wall
### Run the Program
./file_explorer3
### 🧪 Sample Operations
| Option | Description |
|:-------:|-------------|
| 1️⃣ | List files in the current directory |
| 2️⃣ | Show current working path |
| 3️⃣ | Change directory |
| 4️⃣ | Create a new file |
| 5️⃣ | Delete a file |
| 6️⃣ | Rename or move a file |
| 7️⃣ | Copy a file |
| 8️⃣ | Search for a file |
| 9️⃣ | Show file permissions |
| 🔟 | Change file permissions |

📆 Development Stages

Day 1: Designed the structure and implemented file listing.
Day 2: Added directory navigation features.
Day 3: Implemented file manipulation (create, delete, rename, copy).
Day 4: Integrated recursive file search.
Day 5: Added file permission management and logging.

🚀 Future Enhancements

.Add a graphical user interface (GUI) version using Qt or GTK.

.Implement a file preview option for text files.

.Add multi-threading for faster file operations.

.Support ZIP file compression/decompression.

.Enable network file access for remote directories.

👩‍💻 Author

Vaishnabi Palo
Roll No: 2241016040
Department of Computer Science and Engineering
Siksha 'O' Anusandhan University

🏁 License

This project is created for educational purposes under the guidance of the Linux OS Lab Assignment.
You are free to use and modify it with proper credit to the author.
