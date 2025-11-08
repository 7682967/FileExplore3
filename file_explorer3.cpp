#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <vector>
#include <ctime>

using namespace std;

// ---------- Utilities ----------

// Clear terminal screen
void clearScreen() { system("clear"); }

// Format file size in human readable form
string formatSize(off_t size) {
    if (size < 1024) return to_string(size) + " B";
    else if (size < 1024*1024) return to_string(size/1024) + " KB";
    else return to_string(size/(1024*1024)) + " MB";
}

// Format timestamp nicely
string formatTime(time_t t) {
    char buffer[26];
    ctime_r(&t, buffer);
    buffer[strlen(buffer)-1] = 0; // remove newline
    return string(buffer);
}

// ---------- Logging ----------

// Log actions like create, delete, rename
void logAction(const string &msg) {
    ofstream logFile("file_explorer.log", ios::app);
    if (logFile) logFile << formatTime(time(nullptr)) << " - " << msg << endl;
}

// ---------- Banner ----------
void showBanner() {
    cout << "\033[1;36m============================================\n";
    cout << "     🌟 Linux File Explorer Application 🌟   \n";
    cout << "============================================\033[0m\n\n";
}

// ---------- Pause ----------
void pauseScreen() {
    cout << "\n\033[1;34mPress Enter to continue...\033[0m";
    cin.ignore();
    cin.get();
}

// ---------- File Operations ----------

// Recursive listing of files and directories
void listFilesRecursive(const string &path, int indent=0) {
    DIR *dir = opendir(path.c_str());
    if (!dir) {
        perror("Unable to open directory");
        return;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (!strcmp(entry->d_name,".") || !strcmp(entry->d_name,"..")) continue;
        string fullPath = path + "/" + entry->d_name;

        struct stat info;
        if (stat(fullPath.c_str(), &info) < 0) continue;

        string type, color;
        if (S_ISDIR(info.st_mode)) { type = "Dir"; color = "\033[1;34m"; }
        else if (info.st_mode & S_IXUSR) { type = "Exe"; color = "\033[1;32m"; }
        else type = "File", color = "\033[0m";

        cout << string(indent*2,' ') << color << entry->d_name << "\033[0m"
             << " [" << type << ", " << formatSize(info.st_size) << ", "
             << formatTime(info.st_mtime) << "]\n";

        if (S_ISDIR(info.st_mode))
            listFilesRecursive(fullPath, indent+1);
    }
    closedir(dir);
}

// Show current working directory
void showCurrentPath() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    cout << "\n📍 Current directory: \033[1;32m" << cwd << "\033[0m\n";
}

// Change to another directory
void changeDirectory() {
    string path;
    cout << "\nEnter directory to navigate: ";
    cin >> path;
    if (chdir(path.c_str()) == 0)
        cout << "✅ Moved to directory: " << path << endl;
    else
        perror("❌ Directory not found");
}

// Create a new empty file
void createFile() {
    string name;
    cout << "\nEnter filename to create: ";
    cin >> name;
    ofstream file(name);
    if (file) {
        cout << "✅ File '" << name << "' created successfully.\n";
        logAction("Created file: " + name);
    } else cout << "❌ Error creating file.\n";
}

// Delete a file
void deleteFile() {
    string name;
    cout << "\nEnter filename to delete: ";
    cin >> name;
    if (remove(name.c_str()) == 0) {
        cout << "🗑️ File '" << name << "' deleted successfully.\n";
        logAction("Deleted file: " + name);
    } else perror("❌ Error deleting file");
}

// Rename or move a file
void renameFile() {
    string oldName, newName;
    cout << "\nEnter existing filename: "; cin >> oldName;
    cout << "Enter new filename or path: "; cin >> newName;
    if (rename(oldName.c_str(), newName.c_str()) == 0) {
        cout << "✅ File renamed/moved successfully.\n";
        logAction("Renamed/moved: " + oldName + " -> " + newName);
    } else perror("❌ Error renaming/moving file");
}

// Copy a file from source to destination
void copyFile() {
    string src, dst;
    cout << "\nEnter source file: "; cin >> src;
    cout << "Enter destination file: "; cin >> dst;

    ifstream in(src, ios::binary);
    ofstream out(dst, ios::binary);

    if (in && out) {
        out << in.rdbuf();
        cout << "✅ File copied successfully.\n";
        logAction("Copied file: " + src + " -> " + dst);
    } else cout << "❌ Error copying file.\n";
}

// ---------- Search ----------

// Recursively search for a file
void searchFile(const string &name, const string &path=".") {
    DIR *dir = opendir(path.c_str());
    if (!dir) return;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (!strcmp(entry->d_name,".") || !strcmp(entry->d_name,"..")) continue;
        string fullPath = path + "/" + entry->d_name;

        struct stat info;
        if (stat(fullPath.c_str(), &info) < 0) continue;

        if (strcasecmp(entry->d_name, name.c_str()) == 0)
            cout << "🔍 Found: " << fullPath << endl;

        if (S_ISDIR(info.st_mode))
            searchFile(name, fullPath);
    }
    closedir(dir);
}

// ---------- Permissions ----------

// Display permissions of a file
void showPermissions() {
    string name; cout << "\nEnter filename: "; cin >> name;
    struct stat info;
    if (stat(name.c_str(), &info) < 0) { perror("Error"); return; }
    cout << "🔐 Permissions: ";
    cout << ((info.st_mode & S_IRUSR)?"r":"-");
    cout << ((info.st_mode & S_IWUSR)?"w":"-");
    cout << ((info.st_mode & S_IXUSR)?"x":"-");
    cout << ((info.st_mode & S_IRGRP)?"r":"-");
    cout << ((info.st_mode & S_IWGRP)?"w":"-");
    cout << ((info.st_mode & S_IXGRP)?"x":"-");
    cout << ((info.st_mode & S_IROTH)?"r":"-");
    cout << ((info.st_mode & S_IWOTH)?"w":"-");
    cout << ((info.st_mode & S_IXOTH)?"x":"-") << endl;
}

// Change permissions of a file
void changePermissions() {
    string name; int mode;
    cout << "\nEnter filename: "; cin >> name;
    cout << "Enter permission mode (e.g., 777): "; cin >> oct >> mode;
    if (chmod(name.c_str(), mode) == 0) {
        cout << "✅ Permissions updated.\n";
        logAction("Permissions changed: " + name);
    } else perror("❌ Failed to change permissions");
}

// ---------- Menu ----------

// Display main menu with options
void printMenu() {
    cout << "\n================ Linux File Explorer ================\n";
    cout << "1️⃣  List Files (Recursive)\n";
    cout << "2️⃣  Show Current Path\n";
    cout << "3️⃣  Change Directory\n";
    cout << "4️⃣  Create New File\n";
    cout << "5️⃣  Delete File\n";
    cout << "6️⃣  Rename / Move File\n";
    cout << "7️⃣  Copy File\n";
    cout << "8️⃣  Search File\n";
    cout << "9️⃣  Show File Permissions\n";
    cout << "🔟  Change File Permissions\n";
    cout << "0️⃣  Exit\n";
    cout << "====================================================\n";
    cout << "👉 Enter your choice: ";
}

// ---------- Main ----------

int main() {
    int choice;

    while (true) {
        clearScreen();
        showBanner();
        printMenu();
        cin >> choice;
        cin.ignore(); // ignore leftover newline

        switch(choice) {
            case 1: listFilesRecursive("."); pauseScreen(); break;
            case 2: showCurrentPath(); pauseScreen(); break;
            case 3: changeDirectory(); pauseScreen(); break;
            case 4: createFile(); pauseScreen(); break;
            case 5: deleteFile(); pauseScreen(); break;
            case 6: renameFile(); pauseScreen(); break;
            case 7: copyFile(); pauseScreen(); break;
            case 8: {
                string fname; cout << "Enter filename to search: "; cin >> fname;
                searchFile(fname); pauseScreen();
                break;
            }
            case 9: showPermissions(); pauseScreen(); break;
            case 10: changePermissions(); pauseScreen(); break;
            case 0: cout << "\n👋 Exiting File Explorer. Goodbye!\n"; return 0;
            default: cout << "❌ Invalid choice. Try again.\n"; pauseScreen();
        }

        // Small separator between operations
        cout << "\n----------------------------------------------------\n";
    }
}
