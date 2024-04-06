#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <conio.h>
#include <algorithm>

using namespace std;

struct MenuOption {
    string menu_name;
    vector<int> access_role;
};

struct User {
    string fullname;
    string username;
    string password;
    int role;
};

map<int, MenuOption> mainCourse = {
    {1, {"Data Mobil", {1,2}}},
    {2, {"Transaksi", {1,2}}},
    {3, {"Informasi Layanan", {1,2}}},
    {4, {"Search", {1}}},
    {0, {"Logout", {1,2}}}
};

map<int, MenuOption> dataMobil = {
    {1, {"Add car data", {1}}},
    {2, {"Edit car data", {1}}},
    {3, {"Delete car data", {1}}},
    {0, {"Kembali", {1,2}}}
};

map<int, MenuOption> transaction = {
    {1, {"Cash", {2}}},
    {2, {"Transfer", {2}}},
    {0, {"Kembali", {1,2}}}
};

map<int, MenuOption> serviceInformation = {
    {1, {"Add services", {1}}},
    {2, {"Edit services", {1}}},
    {3, {"Delete services", {1}}},
    {0, {"Kembali", {1,2}}}
};

vector<User> list_of_user = {
    {"Admin", "admin", "1234", 1},
    {"Customer", "customer", "1234", 2}
};

User user_information;
bool login = false;

void showMenu(map<int, MenuOption>& daftarMenu, string title);
void authentication();
void addUser(vector<User>& users);

int main() {
    while (true) {
        // checking user authentication
        if (!login) authentication();

        cout << "Welcome, " << user_information.username << "!" << endl;

        do {
            cout << "Choose an option:" << endl;
            int pilihan = showMenu(mainCourse, "Main Menu");

            

            switch (pilihan) {
            case 1:
                showMenu(dataMobil, "Data Mobil Menu");
                break;
            case 2:
                showMenu(transaction, "Transaksi Menu");
                break;
            case 3:
                showMenu(serviceInformation, "Informasi Layanan Menu");
                break;
            case 4:
                cout << "Search option selected." << endl;
                break;
            case 0:
                cout << "Logging out..." << endl;
                authentication();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (pilihan != 0);
    }
    return 0;
}

void authentication() {
    string username;
    char password[100];
    bool user_found = false;

    while (true) {
        if (!user_found) cout << " > username: ", getline(cin, username);
        cout << " > password: ";

        // replace password char into '*"
        char char_input;
        int i = 0;
        while (true) {
            char_input = _getch();
            if (char_input == 13) {
                password[i] = '\0';
                break;
            }
            else if (char_input == '\b') {
                if (i >= 1) {
                    cout << "\b \b";
                    i--;
                }
            }
            else {
                password[i] = char_input;
                cout << "*";
                i++;
            }
        }
        cout << endl;

        auto find_user = find_if(list_of_user.begin(), list_of_user.end(), [username](const User& user) {
            return user.username == username;
            });

        if (find_user != list_of_user.end()) {
            user_found = true;
            if (find_user->password == password) {
                login = true;
                user_information = {
                    find_user->fullname,
                    find_user->username,
                    find_user->password,
                    find_user->role
                };
                break;
            }
            else {
                cout << "password don't match" << endl;
            }
        }
        else {
            user_found = false;
            cout << "username not found" << endl;
        }
    }
    system("cls");
}

void showMenu(map<int, MenuOption>& daftarMenu, string title) {
    /*cout << title << endl;
    for (auto& menu : daftarMenu) {
        cout << menu.first << ") " << menu.second.menu_name << endl;
    }*/

    vector<int> list_available_menu = { 0 };
    int option_selected;

    // display menu options
    cout << "Actions:" << endl;

    int key = 1;
    for (auto& menu : daftarMenu) {
        for (auto& role : menu.second.access_role) {
            if (role == user_information.role) {
                list_available_menu.push_back(menu.first);
                cout << key << ") " << menu.second.menu_name << " | ";
                key++;
                break;
            }
        }
    }
    cout << "0) Exit" << endl;

    cout << endl;

    while (true) {
        cout << "Choose action: ", cin >> option_selected;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        for (auto& menu : daftarMenu) {
            if (option_selected < list_available_menu.size()) {
                return list_available_menu[option_selected];
                break;
            }
        }

        cout << "Choose an available action!" << endl;

    }

    system("pause");
}
