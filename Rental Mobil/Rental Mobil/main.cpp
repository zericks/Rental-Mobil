#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <conio.h>
#include <unordered_map>
#include <limits>
#include <functional>
#include <sstream>

using namespace std;

struct User {
	string fullname;
	string username;
	string password;
	int role;
};

struct MenuOption {
	string menu_name;
	vector<int> access_role;
};

struct Car {
	string brand;            // Merk mobil
	string seri;             // Seri mobil
	string color;            // Warna mobil
	string platNum;          // Nomor plat mobil
	int release_year;        // Tahun rilis mobil
	int capacity;            // Kapasitas penumpang
	int price;               // Harga sewa
};


struct Transaction {
	string transferor_name;  // Nama pentransfer
	string phone_number;     // Nomor HP
	string bank;             // Bank
	string account_number;   // Nomor Rekening
	string address;          // Alamat
	string NIK;              // Nomor Induk Kependudukan (NIK)
	double amount;           // Jumlah transaksi
	int transaction_hour;    // Jam transaksi
	int transaction_day;     // Hari transaksi
	int transaction_month;   // Bulan transaksi
	int transaction_year;    // Tahun transaksi
	string payment_method;   // Metode pembayaran
	double additional_fee;   // Biaya tambahan
};


/*
* Role of User
* untuk menciptakan batas-batasan dalam menggunakan aplikasi ini berdasarkan role user yang digunakan untuk login
*/
map <int, string> role_of_user = {
	{1, "Admin"},
	{2, "Costumer"}
};

vector <User> list_of_user = {
	{"Admin","admin","12345", 1},
	{"Costumer","costumer","12345", 2}
};

//map<int, string> menuUtama = {
//	{1, "Data Mobil"},
//	{2, "Transaksi"},
//	{3, "Search"},
//	{4, "Informasi Layanan"},
//	{0, "Log Out"},
//};

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

User user_information;

void loginPage();
void authentication();
void showAndSelectMenuUtama(map<int, MenuOption> daftarMenu, string title);


int main()
{
	loginPage();

	showAndSelectMenuUtama(mainCourse, "Menu Utama");
    

	return 0;
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> LOGIN <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void loginPage()
{
	
}

void authentication()
{

}


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> MENU <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//void showAndSelectMenuUtama()
//{
//	cout << "Menu yang tersedia:\n";
//	for (auto menu : list_of_menu) {
//		if (menu.first != 0) {
//			cout << " " << menu.first << ") " << menu.second << endl;
//		}
//	}
//	cout << " 0) " << list_of_menu[0] << endl;
//	cout << endl;
//
//	while (true) {
//		int pilihan;
//		cout << "Pilih Menu: ", cin >> pilihan;
//
//		for (auto menu : list_of_menu) {
//			if (menu.first == pilihan) return pilihan;
//		}
//
//		cout << "Mohon pilih menu yang tersedia!" << endl;
//	}
//
//	system("pause");
//	return 0;
//}


void showAndSelectMenuUtama(map<int, MenuOption> daftarMenu, string title)
{
	vector<int> menuTersedia = { 0 };
	int pilihan;

	cout << title << endl;

	int num = 1;
	for (auto& menu : daftarMenu) {
		for (auto& role : menu.second.access_role) {
			if (role == user_information.role) {
				menuTersedia.push_back(menu.first);
				cout << num << ") " << menu.second.menu_name << endl;
				num++;
				break;
			}
		}
	}
	cout << "0) Keluar" << endl;
	cout << endl;

	while (true) {
		cout << "Choose action: ", cin >> pilihan;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		for (auto& menu : daftarMenu) {
			if (pilihan < menuTersedia.size()) {
				return menuTersedia[pilihan];
				break;
			}
		}

		cout << "Choose an available action!" << endl;

	}

	system("pause");
}
