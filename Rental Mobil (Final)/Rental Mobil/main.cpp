/*
	Program Pengelolaan Rental Mobil
	Tugas UAS Struktur Data
    by:
    Kelompok 6
    Ulfiyatun Solekha       23.11.5708
    Junior Yesaya Awawangi  23.11.5722
    Zerick Syahputra        23.11.5729
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <conio.h>
#include <unordered_map>
#include <limits>
#include <functional>
#include <cstring> 
#include <cctype>
#include <algorithm>

using namespace std;

struct Admin {
    string fullname;
    string username;
    string password;
};

struct Car {
    string brand;            // Merk mobil
    string series;           // Seri mobil
    string color;            // Warna mobil
    string platNum;          // Nomor plat mobil
    int release_year;        // Tahun rilis mobil
    int capacity;            // Kapasitas penumpang
    int price;               // Harga sewa
    bool available;          // Ketersediaan mobil
};

struct Service {
    string name;
    char description[100];
    int price;
};

struct Transaction {
    string transferor_name;  // Nama pentransfer
    string phone_number;     // Nomor HP
    string address;          // Alamat
    string NIK;              // Nomor Induk Kependudukan (NIK)
    string job;                  // Pekerjaan
    string transaction_time;     // Waktu transaksi
    string car_rental_brand;     // Merk mobil yang disewa
    string car_rental_series;    // Seri mobil yang disewa
    int car_rental_release;      // Tahun rilis mobil
    string car_rental_platNum;   // Plat nomor mobil yang disewa
    int car_rental_price;        // Harga sewa mobil
    int duration;                // Lama sewa
    string payment_method;       // Metode pembayaran
    int discount;                // Diskon 
    int additional_fee;          // Biaya tambahan
    vector<Service> additional_services;
    int amount;                  // Jumlah transaksi

};

const int MAX_STACK_SIZE = 100;

struct Stack
{
    int top;
    Transaction data[MAX_STACK_SIZE];
};

Stack stack;

const int MAX_QUEUE_SIZE = 3;

struct Queue {
    int depan, belakang, ukuran;
    int data[MAX_QUEUE_SIZE];
};

unordered_map<string, Queue> queues;
Queue queue;
static int preOrderNumber = 1;
int nomorAntrianDipanggil = -1;

struct Kolom {
    string nama;
    string field;
    string align;
};

// Pengaturan informasi bawaan
Admin admins[100]; // Batasi jumlah maksimal admin

int jumlahAdmin = 1; // Sudah ada 1 admin bawaan

Admin defaultAdmin = { "Admin", "admin", "11111" };

vector <Car> list_of_cars = {
    {"Toyota", "Avansa", "Hitam", "AB 1111 TX", 2003, 7, 200000, true},
};

vector <Service> services = {
    {"Paket Supir", "Paket tambahan untuk mendapatkan supir pribadi.", 50000},
    {"Paket GPS", "Paket navigasi GPS untuk membantu Anda menemukan rute perjalanan.", 20000},
};

// DEKLARASI VARIABLE
map<int, string> loginMenu = {
    {0, "Exit"},
    {1, "Login"},
    {2, "Registrasi"},
    {3, "Lupa password atau username"}
};

map<int, string> mainCourse = {
    {0, "Exit"},
    {1, "Data Mobil"},
    {2, "Informasi Layanan"},
    {3, "Transaksi"},
    {4, "Search"},
    {5, "Log Out"},
};

map<int, Kolom> daftarKolom = {
    {0, {"No", "-", "right"}},
    {1, {"Merk", "brand", "left"}},
    {2, {"Seri/Model", "series", "left"}},
    {3, {"Warna", "color", "left"}},
    {4, {"Plat Nomor", "platNum", "left"}},
    {5, {"Tahun Rilis", "release_year", "right"}},
    {6, {"Kapasitas", "capacity", "right"}},
    {7, {"Harga Sewa", "price", "right"}},
    {8, {"Available", "available", "left"}}
};

map<int, Kolom> daftarKolomLayanan = {
    {0, {"No", "-", "right"}},
    {1, {"Nama Layanan", "name", "left"}},
    {2, {"Deskripsi", "description", "left"}},
    {3, {"Harga (Rp)", "price", "right"}}
};

map<int, Kolom> daftarKolomTransaksi = {
    {0, {"No", "-", "right"}},
    {1, {"Waktu Transaksi", "transaction_time", "left"}},
    {2, {"Nama Konsumen", "transferor_name", "left"}},
    {3, {"Metode Pembayaran", "payment_method", "left"}},
    {4, {"Status Pembayaran", "status_pembayaran", "left"}}
};

map<int, string> dataMobil = {
    {0, "Kembali"},
    {1, "Tambah mobil"},
    {2, "Edit mobil"},
    {3, "Hapus mobil"},
};

map<int, string> serviceInformation = {
    {0, "Kembali"},
    {1, "Tambah layanan"},
    {2, "Edit layanan"},
    {3, "Hapus layanan"},
};

map<int, string> transaction = {
    {0, "Kembali"},
    {1, "Pemesanan"},
    {2, "Pre-Order"},
    {3, "Pengembalian"},
    {4, "Riwayat Pemesanan"},
};

map<int, string> preOrder = {
    {0, "Kembali"},
    {1, "Tambah Antrian"},
    {2, "Panggil Antrian"},
    //{2, "Lihat Detail Antrian"},
};

map<int, string> history = {
    {0, "Kembali"},
    {1, "Lihat Detail"},
    {2, "Kosongkan Riwayat Transaksi"},
};

map<int, string> pencarian = {
    {0, "Kembali"},
    {1, "Cari Mobil"},
    {2, "Cari Konsumen"},
};

vector<Service> list_of_services;

void showHeaderBox(string title = "Rental", char align = 'l');
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> LOGIN PAGE <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
int loginPage();
void login(Admin* admins, int data);
bool loginProcess(Admin* admins, int data);
void registrasi(Admin* admins, int& data);
void lupa(Admin* admins, int data);
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PILIHAN MENU <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
int showAndSelectMenu(map<int, string> daftarMenu, string title);
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> KEPUTUSAN <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
bool verify(string text);
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> DATA MOBIL <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void insertionSortCar(vector<Car>& daftarMobil = list_of_cars); // mengurutkan harga sewa dari yang terkecil
void displayCar(vector<Car>& daftarMobil = list_of_cars);
void menuMobil();
void addCar();
void editCar();
void deleteCar();
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> INFORMASI LAYANAN <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void insertionSortServices(vector<Service>& services); // mengurutkan harga layanan dari yang terkecil
void displayServices(vector<Service>& services);
void menuService();
void addService();
void editService();
void deleteService();
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> TRANSAKSI <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void menuTransaction();
// Stack
void inisialisasiStack();
void pushStack(const Transaction& newTransaction);
bool StackIsEmpty();
bool StackIsFull();
void StackClear();       // mengosongkan semua stack sekaligus
// Queue
void inisialisasiQueue(Queue& queue);       // Inisialisasi queue
bool QueueIsEmpty(const Queue& queue);
bool QueueIsFull(const Queue& queue);
void enqueue(const string& platNum, int data);
int dequeue(const string& platNum);
void clear(const string& platNum);
bool queueIsEmpty(const string& platNum);
bool queueIsFull(const string& platNum);
void printQueue(const string& platNum);

// fitur transaksi
void updateCarAvailability(const string& platNum);
void carReservation();
void printNote(const Transaction& transactions);

void displayPreOrderQueue();
void carPreOrder(const string& platNum);
void menuPreOrder();

void carReturn();
void historyTransaction();                    // menampilkan list riwayat transaksi
void showTransactionDetails(int index);
void menuHistory();
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SEARCH <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void menuSearch();

int main() {
    admins[0] = defaultAdmin; // Menambahkan admin bawaan ke dalam daftar admin
    // Menu Login
    int loginStatus;
    do {
        loginStatus = loginPage();
        if (loginStatus == 0) {
            cout << "Good Bye!" << endl;
            return 0;
        }
    } while (loginStatus != 1);

    inisialisasiStack();
    inisialisasiQueue(queue);

    // Menu Utama
    while (loginStatus) {
        system("cls");
        cout << "===========================================================" << endl;
        cout << "||                                                       ||" << endl;
        cout << "||           W E L C O M E   T O   R E N T A L           ||" << endl;
        cout << "||                                                       ||" << endl;
        cout << "===========================================================" << endl;
        switch (showAndSelectMenu(mainCourse, "Menu Utama")) {
        case 1:                           // Data Mobil
            menuMobil();
            break;
        case 2:                           // Informasi Layanan
            menuService();
            break;
        case 3:                           // Transaksi
            menuTransaction();
            break;
        case 4:                           // Search
            menuSearch();
            break;
        case 5:                           // Log Out
            if (verify("Log Out?")) {
                system("cls");
                loginPage();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            system("cls");
            break;
        case 0:                           // Exit
            cout << "Good Bye!" << endl;
            return 0;
        default:
            cout << "Pilihan menu tidak tersedia!" << endl;
            system("pause");
            system("cls");
            break;
        }
    }
    return 0;
}

void showHeaderBox(string title, char align) {

    string horizontal_line;
    for (int i = 0; i < (title.length() + 2); i++) horizontal_line += char(196);

    cout << char(218) << horizontal_line << char(191) << endl;
    cout << char(179) << " ";
    cout << setw(title.length()) << (tolower(align) == 'r' ? right : left) << title;
    cout << " " << char(179) << endl;
    cout << char(192) << horizontal_line << char(217) << endl;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> LOGIN PAGE <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
int loginPage() {
    while (true) {
        int choice;
        system("cls");
        showHeaderBox("LOGIN | RENTAL MOBIL");
        switch (showAndSelectMenu(loginMenu, "Menu")) {
        case 1:                           // Login admin
            login(admins, jumlahAdmin);
            return 1;
            break;
        case 2:                           // Registrasi admin baru
            registrasi(admins, jumlahAdmin);
            break;
        case 3:                           // Lupa username atau password
            lupa(admins, jumlahAdmin);
            break;
        case 0:                           // Exit
            return 0;
        default:
            system("cls");
            cout << "Menu tidak tersedia!\n" << endl;
            break;
        }
    }
}

void login(Admin* admins, int data)
{
    system("cls");
    bool loginBerhasil = false;
    do {
        loginBerhasil = loginProcess(admins, data);
        if (!loginBerhasil) {
            char pilihan;
            cout << "\nLogin gagal. Apakah Anda ingin mencoba lagi? (y/n): ";
            cin >> pilihan;

            if (tolower(pilihan) != 'y') {
                loginPage();
                //return; // Keluar dari fungsi login() jika pengguna tidak ingin mencoba lagi
            }
            system("cls");
        }
    } while (!loginBerhasil);
    system("pause");
    system("cls");
}

bool loginProcess(Admin* admins, int data)
{
    string username, password;
    showHeaderBox("LOGIN | RENTAL MOBIL");
    cout << " > Username: ";
    cin >> username;
    cout << " > Password: ";
    char ch;                             // Merubah password menjadi *
    password = "";
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
        }
        else {
            cout << '*';
            password.push_back(ch);
        }
    }

    for (int i = 0; i < data; ++i) {
        if (admins[i].username == username && admins[i].password == password) {
            cout << "\n\nLogin berhasil. Selamat datang, " << admins[i].fullname << "!" << endl;
            return true;
        }
    }
    return false;
}

void registrasi(Admin* admins, int& data)
{
    system("cls");
    showHeaderBox("REGISTRASI");
    string fullname, username, password;
    cout << "Masukkan detail informasi baru:" << endl;
    cout << " > Nama lengkap : ";
    cin.ignore();
    getline(cin, fullname);

    bool usernameUsed;
    do {
        cout << " > Username     : ";
        cin >> username;
        usernameUsed = false;
        // Cek apakah username sudah digunakan
        for (int i = 0; i < data; ++i) {
            if (admins[i].username == username) {
                cout << "Username sudah digunakan. Silakan pilih username lain." << endl;
                usernameUsed = true;
                break;
            }
        }
    } while (usernameUsed);
    cout << " > Password     : ";
    cin >> password;

    // Tambahkan admin baru ke database
    admins[data].fullname = fullname;
    admins[data].username = username;
    admins[data].password = password;
    data++;

    cout << "\nRegistrasi berhasil!" << endl;
    system("pause");
}

void lupa(Admin* admins, int data)
{
    system("cls");
    showHeaderBox("LUPA?");
    string fullname, username, password, searchKey;
    cout << "Masukkan nama lengkap atau username Anda" << endl;
    cout << " > ";
    cin.ignore();
    getline(cin, searchKey);

    // Cari username pada database
    bool found = false;
    for (int i = 0; i < data; ++i) {
        if (admins[i].fullname == searchKey || admins[i].username == searchKey) {
            found = true;
            cout << endl;
            cout << "------ Informasi Admin ------" << endl;
            cout << " > Nama lengkap : " << admins[i].fullname << endl;
            cout << " > Username     : " << admins[i].username << endl;
            cout << " > Password     : " << admins[i].password << endl;
            cout << endl;
            break;
        }
    }
    if (!found) {
        cout << "\nData tidak ditemukan. Silakan coba lagi." << endl;
    }
    system("pause");
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Pilihan Menu <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
int showAndSelectMenu(map<int, string> daftarMenu, string title)
{
    cout << title << ":" << endl;

    int key = 1;
    for (auto menu : daftarMenu) {
        if (menu.first != 0) {
            cout << " " << key << ") " << menu.second << endl;
            key++;
        }
    }
    cout << " 0) " << daftarMenu[0] << endl;
    cout << endl;

    while (true) {
        int pilihan;
        cout << "Pilih Menu: ", cin >> pilihan;

        for (auto menu : daftarMenu) {
            if (menu.first == pilihan) return pilihan;
        }

        cout << "Mohon pilih menu yang tersedia!" << endl;
    }

    system("pause");
    return 0;
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Keputusan <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
bool verify(string text)
{
    char verif;
    while (true) {
        cout << text << " ( Y / N ): ";

        if (cin >> verif) {
            if (tolower(verif) == 'y' || tolower(verif) == 'n') {
                break;
            }
        }

        cout << "Please input the correct answer Yes or No ( Y / N )!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return tolower(verif) == 'y' ? true : false;
    return false;
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Data Mobil <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void insertionSortCar(vector<Car>& daftarMobil) {      // mengurutkan harga sewa dari yang terkecil
    int n = daftarMobil.size();
    for (int i = 1; i < n; ++i) {
        Car key = daftarMobil[i];
        int j = i - 1;
        while (j >= 0 && daftarMobil[j].price > key.price) {
            daftarMobil[j + 1] = daftarMobil[j];
            --j;
        }
        daftarMobil[j + 1] = key;
    }
}

string ambilDataMobilDenganNamaKolom(const Car& mobil, const string& kolom) {
    if (kolom == "brand") {
        return mobil.brand;
    }
    else if (kolom == "series") {
        return mobil.series;
    }
    else if (kolom == "color") {
        return mobil.color;
    }
    else if (kolom == "platNum") {
        return mobil.platNum;
    }
    else if (kolom == "release_year") {
        return to_string(mobil.release_year);
    }
    else if (kolom == "capacity") {
        return to_string(mobil.capacity);
    }
    else if (kolom == "price") {
        return to_string(mobil.price);
    }
    else if (kolom == "available") {
        return mobil.available ? "Yes" : "No";
    }
    else {
        return "N/A";
    }
}

void displayCar(vector<Car>& daftarMobil)
{
    vector<int> column_width(daftarKolom.size(), 0);
    int total_width = 0;

    // Hitung lebar kolom berdasarkan header
    for (const auto& kolom : daftarKolom) {
        column_width[kolom.first] = kolom.second.nama.length() + 2;
        total_width += column_width[kolom.first] + 1;
    }

    // Hitung lebar kolom berdasarkan data
    for (const auto& mobil : daftarMobil) {
        for (const auto& kolom : daftarKolom) {
            if (kolom.first == 0) continue;
            string value = ambilDataMobilDenganNamaKolom(mobil, kolom.second.field);
            column_width[kolom.first] = max(column_width[kolom.first], static_cast<int>(value.length()) + 2);
        }
    }

    // Hitung total lebar tabel
    total_width = 0;
    for (const auto& width : column_width) {
        total_width += width + 1;
    }

    // Buat garis pembatas
    string line = "+";
    for (const auto& width : column_width) {
        line += string(width, '-') + "+";
    }

    // Cetak header tabel
    cout << line << endl;
    cout << "|";
    for (const auto& kolom : daftarKolom) {
        cout << setw(column_width[kolom.first]) << left << " " + kolom.second.nama << "|";
    }
    cout << endl << line << endl;

    // Cetak isi tabel
    if (daftarMobil.empty()) {
        cout << "|" << setw(total_width - 1) << " Kosong" << "|" << endl;
    }
    else {
        for (size_t i = 0; i < daftarMobil.size(); ++i) {
            cout << "|";
            cout << setw(column_width[0]-1) << right << " " + to_string(i + 1) << " |";
            for (const auto& kolom : daftarKolom) {
                if (kolom.first == 0) continue;
                string value = ambilDataMobilDenganNamaKolom(daftarMobil[i], kolom.second.field);
                if (kolom.second.align == "right") {
                    cout << setw(column_width[kolom.first]) << right << value + " ";
                }
                else {
                    cout << setw(column_width[kolom.first]) << left << " " + value;
                }
                cout << "|";
            }
            cout << endl;
        }
    }
    cout << line << endl;

}

void menuMobil()
{
    bool stay = true;
    while (stay) {
        system("cls");
        showHeaderBox("DAFTAR MOBIL RENTAL");
        // Mengurutkan daftar mobil berdasarkan harga sewa
        insertionSortCar(list_of_cars);
        displayCar(list_of_cars);
        switch (showAndSelectMenu(dataMobil, "Menu")) {
        case 0:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Kembali Ke Menu Utama
            stay = false;
            system("cls");
            break;
        case 1:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Tambah Mobil
            cin.ignore();
            addCar();
            break;
        case 2:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Edit Mobil
            if (!list_of_cars.empty()) {
                cin.ignore();
                editCar();
            }
            else {
                cout << "Daftar Mobil kosong!" << endl;
                system("pause");
            }
            break;
        case 3:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Hapus Mobil
            if (!list_of_cars.empty()) {
                deleteCar();
            }
            else {
                cout << "Daftar Mobil kosong!" << endl;
                system("pause");
            }
            break;
        default:
            cout << "Pilihan menu tidak tersedia!" << endl;
            break;
        }
    }
}

void addCar()
{
    system("cls");

    Car newCar;
    showHeaderBox("TAMBAH MOBIL");
    cout << "Masukkan data mobil baru:" << endl;
    cout << " > Merk        : ", getline(cin, newCar.brand);
    cout << " > Seri/Model  : ", getline(cin, newCar.series);
    cout << " > Warna       : ", getline(cin, newCar.color);
    cout << " > Nomor plat  : ", getline(cin, newCar.platNum);
    cout << " > Tahun rilis : ", cin >> newCar.release_year;
    cout << " > Kapasitas   : ", cin >> newCar.capacity;

    // Validasi input harga sewa
    while (true) {
        cout << " > Harga sewa (per hari) : Rp ";
        if (cin >> newCar.price) {
            // Input valid, keluar dari loop
            break;
        }
        else {
            // Input tidak valid, membersihkan buffer dan mencoba lagi
            cout << "Harga sewa harus berupa angka. Silakan coba lagi." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    newCar.available = true;

    // Tambahkan mobil ke dalam vector
    list_of_cars.push_back(newCar);
    // Tambahkan entri baru ke dalam queues
    queues[newCar.platNum] = Queue();
    cout << "\nData mobil berhasil ditambahkan!" << endl;
    system("pause");
}

void editCar()
{
    int index;
    cout << "Masukkan nomor mobil yang ingin diedit (0 untuk kembali): ";
    cin >> index;
    system("cls");
    showHeaderBox("EDIT MOBIL");

    if (index >= 1 && index <= static_cast<int>(list_of_cars.size())) {
        cin.ignore();

        Car& car = list_of_cars[index - 1];

        cout << "Edit Informasi Mobil " << car.series << endl;
        cout << "1. Merek       : " << car.brand << endl;
        cout << "2. Seri        : " << car.series << endl;
        cout << "3. Warna       : " << car.color << endl;
        cout << "4. Tahun Rilis : " << car.release_year << endl;
        cout << "5. Kapasitas   : " << car.capacity << endl;
        cout << "6. Harga sewa (per hari): Rp " << car.price << endl;

        int option;
        cout << "\nPilih nomor informasi yang akan diedit (0 untuk kembali): ";
        cin >> option;
        cin.ignore();

        switch (option) {
        case 1:
            cout << "Masukkan nama brand/merek baru: ";
            getline(cin, car.brand);
            cout << "Nama merek berhasil diubah menjadi \"" << car.brand << "\"!" << endl;
            break;
        case 2:
            cout << "Masukkan seri baru: ";
            getline(cin, car.series);
            cout << "Nama seri berhasil diubah menjadi \"" << car.series << "\"!" << endl;
            break;
        case 3:
            cout << "Masukkan warna baru: ";
            getline(cin, car.color);
            cout << "Warna berhasil diubah menjadi \"" << car.color << "\"!" << endl;
            break;
        case 4:
            cout << "Masukkan tahun rilis baru: ";
            cin >> car.release_year;
            cout << "Tahun rilis berhasil diubah menjadi \"" << car.release_year << "\"!" << endl;
            break;
        case 5:
            cout << "Masukkan kapasitas penumpang baru: ";
            cin >> car.capacity;
            cout << "Kapasitas penumpang berhasil diubah menjadi \"" << car.capacity << "\"!" << endl;
            break;
        case 6:
            cout << "Masukkan harga sewa baru: Rp ";
            cin >> car.price;
            cout << "Harga sewa (per hari) berhasil diubah menjadi Rp \"" << car.price << "\"!" << endl;
            break;
        case 0:
            break;
        default:
            cout << "Nomor informasi tidak valid." << endl;
            break;
        }
    }
    else if (index != 0) {
        cout << "Nomor mobil tidak valid." << endl;
    }

    system("pause");
    system("cls");
    /*string platNum;
    cout << "Masukkan Nomor Plat Mobil yang ingin diedit: ";
    getline(cin, platNum);

    auto it = find_if(list_of_cars.begin(), list_of_cars.end(), [platNum](const Car& car) {
        return car.platNum == platNum;
        });

    if (it != list_of_cars.end())
    {
        system("cls");
        showHeaderBox("EDIT MOBIL");
        cout << "Edit Informasi Mobil " << it->series << endl;
        cout << "1. Merek       : " << it->brand << endl;
        cout << "2. Seri        : " << it->series << endl;
        cout << "3. Warna       : " << it->color << endl;
        cout << "4. Tahun Rilis : " << it->release_year << endl;
        cout << "5. Kapasitas   : " << it->capacity << endl;
        cout << "6. Harga sewa (per hari): Rp " << it->price << endl;

        int option;
        cout << "\nPilih nomor informasi yang akan diedit (0 untuk kembali): ";
        cin >> option;
        cin.ignore();
        switch (option) {
        case 1:
            cout << "Masukkan nama brand/merek baru: ";
            getline(cin, it->brand);
            cout << "Nama merek berhasil diubah menjadi \"" << it->brand << "\"!" << endl;
            break;
        case 2:
            cout << "Masukkan seri baru: ";
            getline(cin, it->series);
            cout << "Nama seri berhasil diubah menjadi \"" << it->series << "\"!" << endl;
            break;
        case 3:
            cout << "Masukkan warna baru: ";
            getline(cin, it->color);
            cout << "Warna berhasil diubah menjadi \"" << it->color << "\"!" << endl;
            break;
        case 4:
            cout << "Masukkan tahun rilis baru: ";
            cin >> it->release_year;
            cout << "Nama merek berhasil diubah menjadi \"" << it->release_year << "\"!" << endl;
            break;
        case 5:
            cout << "Masukkan kapasitas penumpang baru: ";
            cin >> it->capacity;
            cout << "Kapasitas penumpang berhasil diubah menjadi \"" << it->capacity << "\"!" << endl;
            break;
        case 6:
            cout << "Masukkan harga sewa baru: Rp";
            cin >> it->price;
            cout << "Harga sewa (per hari) berhasil diubah menjadi Rp \"" << it->price << "\"!" << endl;
            break;
        default:
            cout << "Nomor informasi tidak valid." << endl;
            break;
        }
    }
    else {
        cout << "Mobil dengan nomor plat tersebut tidak ditemukan!" << endl;
    }
    system("pause");
    system("cls");*/
}

void deleteCar()
{
    int index;
    cout << "Masukkan nomor mobil yang ingin dihapus: ";
    cin >> index;
    system("cls");

    showHeaderBox("HAPUS MOBIL");

    if (index >= 1 && index <= static_cast<int>(list_of_cars.size())) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        Car& car = list_of_cars[index - 1];
        cout << "Detail Mobil yang akan dihapus:" << endl;
        cout << "Merk Mobil   : " << car.brand << endl;
        cout << "Seri Mobil   : " << car.series << endl;
        cout << "Warna Mobil  : " << car.color << endl;
        cout << "Nomor Plat   : " << car.platNum << endl;
        cout << "Tahun Rilis  : " << car.release_year << endl;
        cout << "Kapasitas    : " << car.capacity << endl;
        cout << "Harga Sewa   : Rp " << car.price << endl << endl;

        if (verify("Apakah Anda yakin ingin menghapus mobil ini?")) {
            list_of_cars.erase(list_of_cars.begin() + (index - 1));
            cout << "Mobil berhasil dihapus!" << endl;
        }
        else {
            cout << "Penghapusan mobil dibatalkan." << endl;
        }
    }
    else {
        cout << "Nomor mobil tidak valid." << endl;
    }
    system("pause");
    system("cls");
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Informasi Layanan <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void insertionSortServices(vector<Service>& services) {
    int n = services.size();
    for (int i = 1; i < n; ++i) {
        Service key = services[i];
        int j = i - 1;
        while (j >= 0 && services[j].price > key.price) {
            services[j + 1] = services[j];
            --j;
        }
        services[j + 1] = key;
    }
}

string ambilDataLayananDenganNamaKolom(const Service& layanan, const string& kolom) {
    if (kolom == "name") {
        return layanan.name;
    }
    else if (kolom == "description") {
        return layanan.description;
    }
    else if (kolom == "price") {
        return to_string(layanan.price);
    }
    else {
        return "N/A";
    }
}

void displayServices(vector<Service>& services) 
{
    vector<int> column_width(daftarKolomLayanan.size(), 0);
    int total_width = 0;

    // Hitung lebar kolom berdasarkan header
    for (const auto& kolom : daftarKolomLayanan) {
        column_width[kolom.first] = kolom.second.nama.length() + 2;
        total_width += column_width[kolom.first] + 1;
    }

    // Hitung lebar kolom berdasarkan data
    for (const auto& layanan : services) {
        for (const auto& kolom : daftarKolomLayanan) {
            if (kolom.first == 0) continue;
            string value = ambilDataLayananDenganNamaKolom(layanan, kolom.second.field);
            column_width[kolom.first] = max(column_width[kolom.first], static_cast<int>(value.length()) + 2);
        }
    }

    // Hitung total lebar tabel
    total_width = 0;
    for (const auto& width : column_width) {
        total_width += width + 1;
    }

    // Buat garis pembatas
    string line = "+";
    for (const auto& width : column_width) {
        line += string(width, '-') + "+";
    }

    // Cetak header tabel
    cout << line << endl;
    cout << "|";
    for (const auto& kolom : daftarKolomLayanan) {
        cout << setw(column_width[kolom.first]) << left << " " + kolom.second.nama << "|";
    }
    cout << endl << line << endl;

    // Cetak isi tabel
    if (services.empty()) {
        cout << "|" << setw(total_width - 1) << " Kosong" << "|" << endl;
    }
    else {
        for (size_t i = 0; i < services.size(); ++i) {
            cout << "|";
            cout << setw(column_width[0] - 1) << right << " " + to_string(i + 1) << " |";
            for (const auto& kolom : daftarKolomLayanan) {
                if (kolom.first == 0) continue;
                string value = ambilDataLayananDenganNamaKolom(services[i], kolom.second.field);
                if (kolom.second.align == "right") {
                    cout << setw(column_width[kolom.first]) << right << value + " ";
                }
                else {
                    cout << setw(column_width[kolom.first]) << left << " " + value;
                }
                cout << "|";
            }
            cout << endl;
        }
    }
    cout << line << endl;
}

void menuService()
{
    bool stay = true;
    while (stay) {
        system("cls");
        showHeaderBox("DAFTAR LAYANAN RENTAL MOBIL");
        // Mengurutkan harga dari yang terkecil
        insertionSortServices(services);
        // Tampilan Layanan Costumer
        displayServices(services);

        switch (showAndSelectMenu(serviceInformation, "Menu")) {
        case 0:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Kembali Ke Menu Utama
            stay = false;
            system("cls");
            break;
        case 1:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Tambah layanan
            //cin.ignore();
            addService();
            break;
        case 2:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Edit layanan
            if (!services.empty()) {
                cin.ignore();
                editService();
            }
            else {
                cout << "Daftar layanan kosong!" << endl;
                system("pause");
            }
            break;
        case 3:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Hapus layanan
            if (!services.empty()) {
                deleteService();
            }
            else {
                cout << "Daftar layanan kosong!" << endl;
                system("pause");
            }
            break;
        default:
            break;
        }
    }
}

void addService()
{
    system("cls");
    showHeaderBox("TAMBAH LAYANAN");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Service newService;
    cout << "Masukkan nama layanan: ";
    getline(cin, newService.name);
    cout << "Masukkan deskripsi layanan (max 200 karakter):" << endl;
    cout << " > "; cin.getline(newService.description, 200);  // Membatasi input deskripsi hingga 200 karakter
    cout << "Masukkan harga layanan (Rp): ";
    cin >> newService.price;

    services.push_back(newService);
    cout << "Layanan berhasil ditambahkan!" << endl;
}

void editService()
{
    int index;
    cout << "Masukkan nomor layanan yang ingin diedit: ";
    cin >> index;
    system("cls");

    showHeaderBox("EDIT LAYANAN");
    if (index >= 1 && index <= static_cast<int>(services.size())) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        Service& service = services[index - 1];
        cout << "Nama layanan saat ini      : " << service.name << endl;
        cout << "Deskripsi layanan saat ini : " << service.description << endl;
        cout << "Harga layanan saat ini     : Rp " << service.price << endl;

        cout << "\nEdit Informasi Layanan " << service.name << ":" << endl;
        cout << "1. Nama layanan" << endl;
        cout << "2. Deskripsi layanan" << endl;
        cout << "3. Harga layanan" << endl;

        int option;
        cout << "\nPilih nomor informasi yang akan diedit (0 untuk kembali): ";
        cin >> option;

        cin.ignore();

        switch (option) {
        case 1:
            cout << "Masukkan nama layanan baru: ";
            getline(cin, service.name);
            cout << "Nama layanan berhasil diubah menjadi \"" << service.name << "\"!" << endl;
            break;
        case 2:
            cout << "Masukkan deskripsi layanan baru: ";
            cin.getline(service.description, 200);
            cout << "Deskripsi layanan berhasil diubah!" << endl;
            break;
        case 3:
            cout << "Masukkan harga layanan baru (Rp): ";
            cin >> service.price;
            cout << "Harga layanan berhasil diubah menjadi Rp " << service.price << "!" << endl;
            break;
        case 0:
            break;
        default:
            cout << "Nomor informasi tidak valid." << endl;
            break;
        }
    }
    else {
        cout << "Nomor layanan tidak valid." << endl;
    }
    system("pause");
    system("cls");
}

void deleteService()
{
    int index;
    cout << "Masukkan nomor layanan yang ingin dihapus: ";
    cin >> index;
    system("cls");

    showHeaderBox("HAPUS LAYANAN");
    if (index >= 1 && index <= static_cast<int>(services.size())) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        Service& service = services[index - 1];
        cout << "Detail Layanan yang akan dihapus:" << endl;
        cout << "Nama layanan      : " << service.name << endl;
        cout << "Deskripsi layanan : " << service.description << endl;
        cout << "Harga layanan     : Rp " << service.price << endl << endl;

        if (verify("Apakah Anda yakin ingin menghapus layanan ini?")) {
            services.erase(services.begin() + (index - 1));
            cout << "Layanan berhasil dihapus!" << endl;
        }
        else {
            cout << "Penghapusan layanan dibatalkan." << endl;
        }
    }
    else {
        cout << "Nomor layanan tidak valid." << endl;
    }
    system("pause");
    system("cls");
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Transaksi <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void menuTransaction()
{
    bool stay = true;
    while (stay) {
        system("cls");
        showHeaderBox("TRANSAKSI");
        switch (showAndSelectMenu(transaction, "Menu Transaksi")) {
        case 0:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Kembali Ke Menu Utama
            stay = false;
            system("cls");
            break;
        case 1:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Pemesan mobil
            if (!StackIsFull()) {
                if (!list_of_cars.empty()) {
                    cin.ignore();
                    carReservation();
                }
                else {
                    cout << "Daftar Mobil kosong!" << endl;
                    system("pause");
                }
            }
            else {
                cout << "Riwayat transaksi penuh! Silahkan kosongkan penyimpanan!" << endl;
                system("pause");
            }
            break;
        case 2:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Pre-Order Mobil
            menuPreOrder();
            break;
        case 3:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Pengembalian Mobil
            carReturn();
            break;
        case 4:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Riwayat pemesanan
            menuHistory();
            break;
        }
    }
}

// .................... Stack
void inisialisasiStack()
{
    stack.top = -1;
}

void pushStack(const Transaction& newTransaction)
{
    if (StackIsFull()) {
        cout << "Stack penuh. Tidak bisa "
        << "menambahkan data transaksi baru." << endl;
    }
    else {
        stack.top++;
        stack.data[stack.top] = newTransaction;
    }
}

bool StackIsEmpty()
{
    return (stack.top == -1);
}

bool StackIsFull()
{
    return (stack.top == MAX_STACK_SIZE);
}

void StackClear()
{
    stack.top = -1;
    cout << "Riwayat sudah dikosongkan" << endl << endl;
}

Transaction top() {
    if (StackIsEmpty()) {
        cout << "Stack kosong." << endl;
        return {};
    }
    else {
        return stack.data[stack.top];
    }
}

// .................... Queue
void inisialisasiQueue(Queue& queue)
{
    queue.depan = queue.belakang = -1;
    queue.ukuran = 0;

    // Masukkan queue ke dalam map untuk setiap mobil
    queues.clear();
    for (const auto& car : list_of_cars) {
        queues[car.platNum] = queue;
    }
}

bool QueueIsEmpty(const Queue& queue)
{
    return (queue.ukuran == 0);
}

bool QueueIsFull(const Queue& queue)
{
    return (queue.ukuran == MAX_QUEUE_SIZE);
}

void enqueue(const string& platNum, int data)
{
    if (!queues.count(platNum)) {
        cout << "Mobil dengan plat nomor " << platNum << " tidak ditemukan." << endl;
        return;
    }

    Queue& queue = queues[platNum];

    if (QueueIsFull(queue)) {
        cout << "Antrian untuk mobil dengan plat nomor " 
            << platNum << " sudah penuh!" << endl;
        return;
    }

    if (QueueIsEmpty(queue))
        queue.depan = 0;

    queue.belakang = (queue.belakang + 1) % MAX_QUEUE_SIZE;
    queue.data[queue.belakang] = data;
    queue.ukuran++;

    cout << "Data berhasil ditambahkan ke antrian mobil " << platNum << endl;
    cout << "Nomor Antrian : " << (queue.belakang + 1) << endl << endl;
}

int dequeue(const string& platNum)
{
    if (!queues.count(platNum)) {
        cout << "Mobil dengan plat nomor " << platNum << " tidak ditemukan." << endl;
        system("pause");
        return -1;
    }

    Queue& queue = queues[platNum];

    if (QueueIsEmpty(queue)) {
        cout << "Antrian untuk mobil dengan plat nomor " << platNum << " kosong!" << endl;
        system("pause");
        return -1;
    }

    int nomorAntrianYangDihapus = queue.data[queue.depan];
    queue.depan = (queue.depan + 1) % MAX_QUEUE_SIZE;
    queue.ukuran--;

    if (QueueIsEmpty(queue)) {
        queue.depan = -1;
        queue.belakang = -1;
    }

    cout << "Antrian mobil " << platNum << " sudah dialihkan" << endl << endl;
    //cout << "Antrian mobil " << platNum << " nomor " << nomorAntrianYangDihapus << " sudah dialihkan" << endl << endl;
    return nomorAntrianYangDihapus;
}

void clear(const string& platNum)
{
    if (!queues.count(platNum)) {
        cout << "Mobil dengan plat nomor " << platNum << " tidak ditemukan." << endl;
        return;
    }

    Queue& queue = queues[platNum];
    queue.depan = queue.belakang = -1;
    queue.ukuran = 0;

    cout << "Antrian untuk mobil dengan plat nomor " << platNum << " sudah dikosongkan" << endl << endl;
}

bool queueIsEmpty(const string& platNum)
{
    if (!queues.count(platNum)) {
        cout << "Mobil dengan plat nomor " << platNum << " tidak ditemukan." << endl;
        return true;
    }

    return (queues[platNum].ukuran == 0);
}

bool queueIsFull(const string& platNum)
{
    if (!queues.count(platNum)) {
        cout << "Mobil dengan plat nomor " << platNum << " tidak ditemukan." << endl;
        return true;
    }

    return (queues[platNum].ukuran == MAX_QUEUE_SIZE);
}

void printQueue(const string& platNum)
{
    if (!queues.count(platNum)) {
        cout << "Mobil dengan plat nomor " << platNum << " tidak ditemukan." << endl;
        return;
    }

    Queue& queue = queues[platNum];

    if (QueueIsEmpty(queue)) {
        cout << "Antrian untuk mobil dengan plat nomor " << platNum << " kosong" << endl << endl;
        return;
    }

    cout << "Isi antrian untuk mobil " << platNum << " : ";
    for (int i = queue.depan; i <= queue.belakang; i++) {
        cout << queue.data[i] << " ";
    }
    cout << endl << endl;
}

// Fitur transaksi
void updateCarAvailability(const string& platNum)
{
    auto it = find_if(list_of_cars.begin(), list_of_cars.end(), [platNum](const Car& car) {
        return car.platNum == platNum;
        });

    if (it != list_of_cars.end()) {
        it->available = false; // Setel ketersediaan ke false untuk mobil yang dipilih
    }
    else {
        cout << "Mobil dengan nomor plat tersebut tidak ditemukan!" << endl;
    }
}

void carReservation()
{
    system("cls");
    int durasi;
    int index;
    string platNum;
    Transaction newTransaction;

    showHeaderBox("PEMESANAN RENTAL MOBIL");

    insertionSortCar(list_of_cars);
    displayCar(list_of_cars); // menampilkan data mobil rental
    cout << "Pilih nomor mobil yang ingin disewa (0 untuk kembali): ";
    cin >> index;

    if (index >= 1 && index <= static_cast<int>(list_of_cars.size()))
    {
        cin.ignore();
        Car& selectedCar = list_of_cars[index - 1];
        if (selectedCar.available) // Mobil tersedia
        {
            // mobil ditemukan, lanjut ke proses transaksi
            system("cls");
            cout << "\nMasukkan data identitas diri anda:" << endl;
            cout << "-------------------------------------" << endl;
            cout << " > Nama             : ", getline(cin, newTransaction.transferor_name);
            cout << " > No. HP           : ", getline(cin, newTransaction.phone_number);
            cout << " > Alamat lengkap   : ", getline(cin, newTransaction.address);
            cout << " > NIK              : ", getline(cin, newTransaction.NIK);
            cout << " > Pekerjaan        : ", getline(cin, newTransaction.job);
            cout << "" << endl;
            cout << " > Waktu transaksi (dd/mm/yyyy) : ", getline(cin, newTransaction.transaction_time);
            cout << " > Lama sewa (hari) : "; cin >> newTransaction.duration;
            cout << "Gunakan layanan tambahan (Y/N): ";
            char use_additional_service;
            cin >> use_additional_service;
            cin.ignore(); 
            if (tolower(use_additional_service) == 'y') {
                int service_index;
                displayServices(services);
                do {
                    cout << "Pilih layanan tambahan (masukkan nomor layanan atau 0 untuk selesai): ";
                    cin >> service_index;
                    if (service_index >= 1 && service_index <= services.size()) {
                        newTransaction.additional_services.push_back(services[service_index - 1]);
                    }
                    else if (service_index != 0) {
                        cout << "Pilihan layanan tidak valid. Silakan pilih kembali." << endl;
                    }
                } while (service_index != 0);
            }
            else {
                newTransaction.additional_fee = 0.0;
            }
            system("cls");

            // Hitung total biaya transaksi
            int total_price = selectedCar.price * newTransaction.duration;
            int total_additional_fee = 0; // Inisialisasi biaya tambahan
            for (const auto& service : newTransaction.additional_services) {
                total_additional_fee += service.price;
            }
            total_price += total_additional_fee;
            // Tampilkan informasi transaksi
            cout << "\n--- Detail Transaksi ---" << endl;
            cout << "Nama Pelanggan   : " << newTransaction.transferor_name << endl;
            cout << "No. HP           : " << newTransaction.phone_number << endl;
            cout << "Alamat           : " << newTransaction.address << endl;
            cout << "NIK              : " << newTransaction.NIK << endl;
            cout << "Pekerjaan        : " << newTransaction.job << endl;
            cout << "Mobil yang disewa: " << selectedCar.brand << " " << selectedCar.series << " (" << selectedCar.platNum << ")" << endl;
            cout << "Waktu transaksi  : " << newTransaction.transaction_time << endl;
            cout << "Lama Sewa (hari) : " << newTransaction.duration << " hari" << endl;
            cout << "Biaya Sewa       : Rp " << selectedCar.price << " per hari" << endl;
            // Tampilkan biaya tambahan dan total biaya
            newTransaction.additional_fee = total_additional_fee;
            cout << "Biaya Tambahan   : Rp " << total_additional_fee << endl;
            for (const auto& service : newTransaction.additional_services) {
                cout << "                   - " << service.name << " (Rp " << service.price << ")" << endl;
            }
            cout << "Total Biaya      : Rp " << total_price << endl;
            if (newTransaction.duration > 7) {
                // Hitung diskon 5%
                int discount = 0.05 * total_price;
                newTransaction.discount = discount;
                // Kurangi diskon dari total biaya
                total_price -= discount;
                cout << "\nAnda mendapatkan diskon 5% karena menyewa mobil lebih dari 7 hari!" << endl;
                cout << "Jumlah diskon    : Rp " << discount << endl;
                cout << "Total Biaya      : Rp " << total_price << endl << endl; // menghitung total biaya transaksi setelah diskon
            }
            else {
                newTransaction.discount = 0.0;
            }

            newTransaction.car_rental_brand = selectedCar.brand;
            newTransaction.car_rental_series = selectedCar.series;
            newTransaction.car_rental_release = selectedCar.release_year;
            newTransaction.car_rental_platNum = selectedCar.platNum;
            newTransaction.car_rental_price = selectedCar.price;
            newTransaction.amount = total_price;

            // Konfirmasi transaksi
            cout << endl;
            if (verify("Apakah Anda yakin ingin melanjutkan transaksi ini?")) {
                // Update car availability
                updateCarAvailability(selectedCar.platNum);

                // Pilihan metode pembayaran
                cout << "\nPilih metode pembayaran: " << endl;
                cout << "1. Cash" << endl;
                cout << "2. Transfer" << endl;
                int payment_method;
                cout << "Masukkan pilihan Anda: "; cin >> payment_method;
                cout << endl;
                switch (payment_method) {
                case 1: // Cash
                    int paid;
                    newTransaction.payment_method = "Cash";
                    cout << "Silakan lakukan pembayaran sebesar Rp " << newTransaction.amount << endl;
                    cout << "Dibayar : Rp "; cin >> paid;
                    if (paid >= newTransaction.amount) {
                        int change = paid - newTransaction.amount;
                        cout << "Kembali : Rp " << change << endl;
                        //cout << "Terima kasih atas pembayarannya." << endl;
                        system("pause");
                    }
                    else {
                        cout << "Jumlah pembayaran tidak mencukupi." << endl;
                        system("pause");
                    }
                    break;
                case 2: // Transfer
                    newTransaction.payment_method = "Transfer";
                    cout << "Silakan lakukan transfer sebesar Rp " << newTransaction.amount << " ke rekening berikut:" << endl;
                    cout << "Bank           : BRI" << endl;
                    cout << "Nomor Rekening : 306902005482622" << endl;
                    cout << "Atas Nama      : Zerick Syahputra" << endl;
                    system("pause");
                    break;
                default:
                    cout << "Pilihan metode pembayaran tidak valid." << endl;
                    break;
                }

                pushStack(newTransaction);
                cout << "Transaksi berhasil dilakukan!" << endl;
                system("pause");
                system("cls");
                // Cetak Nota Transaksi
                printNote(top());
                system("pause");
            }
            else {
                cout << "Transaksi dibatalkan." << endl;
                system("pause");
                system("cls");
            }
        }
        else { // Mobil tidak tersedia
            cout << "Maaf, mobil tersebut sedang tidak tersedia." << endl;
            if (verify("Apakah Anda ingin melanjutkan dengan pre-order?")) {
                cin.ignore();
                carPreOrder(selectedCar.platNum);
            }
        }
    }
    else if (index != 0) {
        // Mobil tidak ditemukan
        cout << "Nomor mobil tidak valid." << endl;
        system("pause");
        system("cls");
    }
}

void printNote(const Transaction& transactions)
{
    string platNum;
    cout << "                       RENTAL MOBIL           " << endl;
    cout << "            Jl. Ring Road Utara - Condongcatur" << endl;
    cout << "                    Telp. 085801627983        " << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << " Nama Penyewa : " << transactions.transferor_name << endl;
    cout << " Nomor HP     : " << transactions.phone_number << endl;
    cout << " Alamat       : " << transactions.address << endl;
    cout << " NIK          : " << transactions.NIK << endl;
    cout << " Pekerjaan    : " << transactions.job << endl << endl;

    cout << " Waktu (dd/mm/yyyy)   : " << transactions.transaction_time << endl;
    cout << " Mobil yang disewa    : " << transactions.car_rental_brand << " " << transactions.car_rental_series << " " << transactions.car_rental_release << " (" << transactions.car_rental_platNum << ")" << endl;
    cout << " Lama sewa            : " << transactions.duration << " hari" << endl;
    cout << " Harga sewa           : " << transactions.car_rental_price << " per hari" << endl;
    cout << " Pembayaran           : " << transactions.payment_method << endl;
    cout << " Tambahan             : Rp " << transactions.additional_fee << endl;
    for (const auto& service : transactions.additional_services) {
        cout << "                        - " << service.name << "( Rp " << service.price << " )" << endl;
    }
    cout << "----------------------------------------------------------" << endl;
    if (transactions.discount != 0.0) {
        cout << " Diskon 5%            : Rp " << transactions.discount << endl;
    }
    cout << " Total Biaya          : Rp " << transactions.amount << endl << endl;
}

// Queue
void displayPreOrderQueue()
{
    system("cls");

    showHeaderBox("DAFTAR ANTRIAN MOBIL");
    // Header tabel
    cout << string(63, '-') << endl; // Garis pemisah
    cout << " " << setw(1) << "No" << " | " << setw(20) << "Merk Brand" << " | " << setw(15) << "Plat Nomor" << " | " << setw(15) << "Jumlah Antrian" << "| "  << endl;
    cout << string(63, '-') << endl; // Garis pemisah

    int nomor = 1;
    for (const auto& entry : queues) {
        const string& platNum = entry.first;
        const Queue& queue = entry.second;

        auto it = find_if(list_of_cars.begin(), list_of_cars.end(), [platNum](const Car& car) {
            return car.platNum == platNum;
            });

        if (it != list_of_cars.end()) {
            cout << "  " << setw(1) << nomor << " | "
                << setw(20) << it->brand + " " + it->series << " | "
                << setw(15) << it->platNum << " | "
                << setw(15) << queue.ukuran << "| " << endl;
            nomor++;
        }
    }
    cout << string(63, '-') << endl; // Garis pemisah
}

void carPreOrder(const string& platNum)
{
    if (!queues.count(platNum)) {
        cout << "Mobil dengan plat nomor " << platNum << " tidak ditemukan." << endl;
        system("pause");
        return;
    }

    if (queueIsFull(platNum)) {
        cout << "Antrian untuk mobil dengan plat nomor " << platNum << " sudah penuh!" << endl;
        system("pause");
        return;
    }

    Transaction newTransaction;

    auto it = find_if(list_of_cars.begin(), list_of_cars.end(), [platNum](const Car& car) {
        return car.platNum == platNum;
        });

    if (it != list_of_cars.end())
    {
        if (!it->available) // mobil tidak tersedia
        {
            // mobil ditemukan, lanjut ke proses pre-order
            system("cls");
            showHeaderBox("   PRE-ORDER MOBIL RENTAL    ");

            cout << "\nMasukkan data identitas diri anda:" << endl;
            cout << "-------------------------------------" << endl;
            cout << " > Nama             : ", getline(cin, newTransaction.transferor_name);
            cout << " > No. HP           : ", getline(cin, newTransaction.phone_number);
            cout << " > Alamat lengkap   : ", getline(cin, newTransaction.address);
            cout << " > NIK              : ", getline(cin, newTransaction.NIK);
            cout << " > Pekerjaan        : ", getline(cin, newTransaction.job);
            cout << "" << endl;
            cout << " > Waktu transaksi (dd/mm/yyyy) : ", getline(cin, newTransaction.transaction_time);
            cout << " > Lama sewa (hari) : "; cin >> newTransaction.duration;
            cout << "Gunakan layanan tambahan (Y/N): ";
            char use_additional_service;
            cin >> use_additional_service;
            cin.ignore(); // Clear the input buffer
            if (tolower(use_additional_service) == 'y') {
                int service_index;
                displayServices(services);
                do {
                    cout << "Pilih layanan tambahan (masukkan nomor layanan atau 0 untuk selesai): ";
                    cin >> service_index;
                    if (service_index >= 1 && service_index <= services.size()) {
                        newTransaction.additional_services.push_back(services[service_index - 1]);
                    }
                    else if (service_index != 0) {
                        cout << "Pilihan layanan tidak valid. Silakan pilih kembali." << endl;
                    }
                } while (service_index != 0);
            }
            else {
                newTransaction.additional_fee = 0.0;
            }
            system("cls");

            // Hitung total biaya transaksi
            int total_price = it->price * newTransaction.duration;
            int total_additional_fee = 0; // Inisialisasi biaya tambahan
            for (const auto& service : newTransaction.additional_services) {
                total_additional_fee += service.price;
            }
            total_price += total_additional_fee;

            // Tampilkan informasi transaksi
            cout << "\n--- Detail Pre-Order ---" << endl;
            cout << "Nama Pelanggan   : " << newTransaction.transferor_name << endl;
            cout << "No. HP           : " << newTransaction.phone_number << endl;
            cout << "Alamat           : " << newTransaction.address << endl;
            cout << "NIK              : " << newTransaction.NIK << endl;
            cout << "Pekerjaan        : " << newTransaction.job << endl;
            cout << "Mobil yang disewa: " << it->brand << " " << it->series << " (" << it->platNum << ")" << endl;
            cout << "Waktu transaksi  : " << newTransaction.transaction_time << endl;
            cout << "Lama Sewa (hari) : " << newTransaction.duration << " hari" << endl;
            cout << "Biaya Sewa       : Rp " << it->price << " per hari" << endl;
            newTransaction.additional_fee = total_additional_fee;
            cout << "Biaya Tambahan   : Rp " << total_additional_fee << endl;
            for (const auto& service : newTransaction.additional_services) {
                cout << "                   - " << service.name << " (Rp " << service.price << ")" << endl;
            }
            cout << "Total Biaya      : Rp " << total_price << endl;
            if (newTransaction.duration > 7) {
                // Hitung diskon 5%
                int discount = 0.05 * total_price;
                newTransaction.discount = discount;
                // Kurangi diskon dari total biaya
                total_price -= discount;
                cout << "\nAnda mendapatkan diskon 5% karena menyewa mobil lebih dari 7 hari!" << endl;
                cout << "Jumlah diskon    : Rp " << discount << endl;
                cout << "Total Biaya      : Rp " << total_price << endl << endl; // menghitung total biaya transaksi setelah diskon
            }
            else {
                newTransaction.discount = 0.0;
            }

            newTransaction.car_rental_brand = it->brand;
            newTransaction.car_rental_series = it->series;
            newTransaction.car_rental_release = it->release_year;
            newTransaction.car_rental_platNum = it->platNum;
            newTransaction.car_rental_price = it->price;
            newTransaction.amount = total_price;

            // Konfirmasi transaksi
            if (verify("Apakah Anda yakin ingin melanjutkan pre-order ini?")) {
                // Update car availability
                updateCarAvailability(platNum);

                // Pilihan metode pembayaran
                cout << "\nPilih metode pembayaran: " << endl;
                cout << "1. Cash" << endl;
                cout << "2. Transfer" << endl;
                int payment_method;
                cout << "Masukkan pilihan Anda: "; cin >> payment_method;
                cout << endl;
                switch (payment_method) {
                case 1: // Cash
                    int paid;
                    newTransaction.payment_method = "Cash";
                    cout << "Silakan lakukan pembayaran sebesar Rp " << newTransaction.amount << endl;
                    cout << "Dibayar : Rp "; cin >> paid;
                    if (paid >= newTransaction.amount) {
                        int change = paid - newTransaction.amount;
                        cout << "Kembali : Rp " << change << endl;
                        system("pause");
                    }
                    else {
                        cout << "Jumlah pembayaran tidak mencukupi." << endl;
                        system("pause");
                    }
                    break;
                case 2: // Transfer
                    newTransaction.payment_method = "Transfer";
                    cout << "Silakan lakukan transfer sebesar Rp " << newTransaction.amount << " ke rekening berikut:" << endl;
                    cout << "Bank           : BRI" << endl;
                    cout << "Nomor Rekening : 306902005482622" << endl;
                    cout << "Atas Nama      : Zerick Syahputra" << endl;
                    system("pause");
                    break;
                default:
                    cout << "Pilihan metode pembayaran tidak valid." << endl;
                    break;
                }

                pushStack(newTransaction);
                cout << "Transaksi berhasil dilakukan!" << endl;
                system("pause");
                system("cls");
                // Cetak Nota Pre-Order
                printNote(top());
                // Enqueue the pre-order number
                enqueue(platNum, preOrderNumber);
                preOrderNumber++;
                cout << "Pre-order berhasil dilakukan!" << endl;
                system("pause");
                system("cls");
            }
            else {
                cout << "Pre-order dibatalkan." << endl;
                system("pause");
                system("cls");
            }
        }
        else { // Mobil tersedia
            cout << "Mobil dengan plat nomor " << platNum << " masih tersedia." << endl;
            if (verify("Apakah Anda ingin melanjutkan ke pemesanan?")) {
                cin.ignore();
                carReservation();
            }
        }
    }
    else {
        // Mobil tidak ditemukan
        cout << "Mobil dengan plat nomor tersebut tidak ditemukan." << endl;
        system("pause");
        system("cls");
    }
}

void menuPreOrder()
{
    bool stay = true;
    while (stay) {
        system("cls");
        string platNum;
        displayPreOrderQueue();
        switch (showAndSelectMenu(preOrder, "Menu")) {
        case 0:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Kembali Ke Menu Utama
            stay = false;
            system("cls");
            break;
        case 1:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Menambahkan antrian
            cout << "Pilih nomor mobil untuk dipesan: ";
            int index;
            cin >> index;
            cin.ignore();
            if (index >= 1 && index <= static_cast<int>(list_of_cars.size())) {
                carPreOrder(list_of_cars[index - 1].platNum);
            }
            else {
                cout << "Nomor mobil tidak valid." << endl;
                system("pause");
            }
            break;
        case 2:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Panggil antrian
            cout << "Masukkan plat nomor mobil: ";
            cin.ignore();
            getline(cin, platNum);
            nomorAntrianDipanggil = dequeue(platNum);
            break;
        }
    }
}

void carReturn()
{
    system("cls");
    string platNum, keyword;

    showHeaderBox("PENGEMBALIAN MOBIL RENTAL");

    cout << "Masukkan Plat Nomor Mobil yang dikembalikan: ";
    cin.ignore();
    getline(cin, platNum);

    auto it = find_if(list_of_cars.begin(), list_of_cars.end(), [platNum](const Car& car) {
        return car.platNum == platNum;
        });

    if (it != list_of_cars.end()) {
        if (!it->available) {
            it->available = true;
            cout << "Mobil dengan plat nomor " << platNum << " telah berhasil dikembalikan." << endl;
            if (!queueIsEmpty(platNum)) {
                cout << "\nTerdapat antrian pre-order untuk mobil dengan plat nomor " << platNum << endl;
                if (verify("> Alihkan mobil ke antrian pre-order?")) {
                    updateCarAvailability(platNum);
                    nomorAntrianDipanggil = dequeue(platNum);

                }
            }
        }
        else {
            cout << "Mobil dengan plat nomor tersebut masih tersedia" << endl;
        }
    }
    else {
        cout << "Mobil dengan plat nomor tersebut tidak ditemukan." << endl;
    }

    system("pause");
    system("cls");
}

string ambilDataTransaksiDenganNamaKolom(const Transaction& transaksi, const string& kolom) {
    if (kolom == "transaction_time") {
        return transaksi.transaction_time;
    }
    else if (kolom == "transferor_name") {
        return transaksi.transferor_name;
    }
    else if (kolom == "payment_method") {
        return transaksi.payment_method;
    }
    else if (kolom == "status_pembayaran") {
        // Logika untuk menentukan status pembayaran bisa ditambahkan di sini
        return "Lunas"; // Contoh status pembayaran
    }
    else {
        return "N/A";
    }
}

void historyTransaction()
{
    system("cls");

    showHeaderBox("RIWAYAT TRANSAKSI");

    vector<int> column_width(daftarKolomTransaksi.size(), 0);
    int total_width = 0;

    // Hitung lebar kolom berdasarkan header
    for (const auto& kolom : daftarKolomTransaksi) {
        column_width[kolom.first] = kolom.second.nama.length() + 2;
        total_width += column_width[kolom.first] + 1;
    }

    // Hitung lebar kolom berdasarkan data
    for (int i = 0; i <= stack.top; ++i) {
        for (const auto& kolom : daftarKolomTransaksi) {
            if (kolom.first == 0) continue;
            string value = ambilDataTransaksiDenganNamaKolom(stack.data[i], kolom.second.field);
            column_width[kolom.first] = max(column_width[kolom.first], static_cast<int>(value.length()) + 2);
        }
    }

    // Hitung total lebar tabel
    total_width = 0;
    for (const auto& width : column_width) {
        total_width += width + 1;
    }

    // Buat garis pembatas
    string line = "+";
    for (const auto& width : column_width) {
        line += string(width, '-') + "+";
    }

    // Cetak header tabel
    cout << line << endl;
    cout << "|";
    for (const auto& kolom : daftarKolomTransaksi) {
        cout << setw(column_width[kolom.first]) << left << " " + kolom.second.nama << "|";
    }
    cout << endl << line << endl;

    // Cetak isi tabel
    if (StackIsEmpty()) {
        cout << "|" << setw(total_width - 1) << " Kosong" << "|" << endl;
    }
    else {
        for (int i = 0; i <= stack.top; ++i) {
            cout << "|";
            cout << setw(column_width[0] - 1) << right << " " + to_string(i + 1) << " |";
            for (const auto& kolom : daftarKolomTransaksi) {
                if (kolom.first == 0) continue;
                string value = ambilDataTransaksiDenganNamaKolom(stack.data[i], kolom.second.field);
                if (kolom.second.align == "right") {
                    cout << setw(column_width[kolom.first]) << right << value + " ";
                }
                else {
                    cout << setw(column_width[kolom.first]) << left << " " + value;
                }
                cout << "|";
            }
            cout << endl;
        }
    }
    cout << line << endl;

}

void showTransactionDetails(int index)
{
    if (index >= 1 && index <= stack.top + 1) {
        system("cls");
        Transaction& transaction = stack.data[index - 1];
        cout << "---- Detail Transaksi ----" << endl;
        cout << " Nama         : " << transaction.transferor_name << endl;
        cout << " No. HP       : " << transaction.phone_number << endl;
        cout << " Alamat       : " << transaction.address << endl;
        cout << " NIK          : " << transaction.NIK << endl;
        cout << " Pekerjaan    : " << transaction.job << endl << endl;
        cout << " Waktu (dd/mm/yyyy) : " << transaction.transaction_time << endl << endl;

        cout << " Mobil yang disewa  : " << transaction.car_rental_brand << " " << transaction.car_rental_series << " " << transaction.car_rental_release << " (" << transaction.car_rental_platNum << ")" << endl;
        cout << " Lama Sewa (hari)   : " << transaction.duration << " hari" << endl;
        cout << " Harga sewa         : " << transaction.car_rental_price << " per hari" << endl;
        cout << " Pembayaran         : " << transaction.payment_method << endl;
        cout << " Biaya Tambahan     : Rp " << transaction.additional_fee << endl;
        for (const auto& service : transaction.additional_services) {
            cout << "                      - " << service.name << "( Rp " << service.price << " )" << endl;
        }
        if (transaction.discount != 0.0) {
            cout << " Diskon 5%          : Rp " << transaction.discount << endl;
        }
        cout << " Total Biaya        : Rp " << transaction.amount << endl << endl;
        system("pause");
    }
    else {
        cout << "Nomor layanan tidak valid." << endl;
        system("pause");
    }
}

void menuHistory()
{
    bool stay = true;
    while (stay) {
        system("cls");
        historyTransaction();
        switch (showAndSelectMenu(history, "Menu")) {
        case 0:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Kembali Ke Menu Utama
            stay = false;
            system("cls");
            break;
        case 1:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Lihat detail transaksi
            if (StackIsEmpty()) {
                cout << "Riwayat transaksi kosong." << endl;
                system("pause");
            }
            else {
                int index;
                cout << "Pilih nomor untuk melihat detail transaksi (tekan 0 untuk kembali):" << endl;
                cout << "Enter number: "; cin >> index;
                if (index != 0) {
                    showTransactionDetails(index);
                }
            }
            break;
        case 2:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Kosongkan riwayat transaksi
            cin.ignore();
            if (verify("Apakah Anda ingin mengosongkan riwayat transaksi?")) {
                StackClear();
            }
            break;
        }
    }
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SEARCH <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void menuSearch()
{
    bool stay = true;
    while (stay) {
        system("cls");
        string searchKey;
        showHeaderBox("SEARCH");
        switch (showAndSelectMenu(pencarian, "Menu")) {
        case 0:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Kembali Ke Menu Utama
            stay = false;
            system("cls");
            break;
        case 1:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Cari mobil
            system("cls");
            showHeaderBox("PENCARIAN DATA MOBIL");
            cout << "Masukkan Plat Nomor atau Seri Mobil: ";
            cin.ignore();
            getline(cin, searchKey);
            searchKey[0] = toupper(searchKey[0]);
            bool ketemu;
            for (const Car& car : list_of_cars) {
                if (car.platNum == searchKey || car.series == searchKey) {
                    ketemu = true;
                    cout << endl;
                    cout << "----- Informasi Mobil -----" << endl;
                    cout << " Merek         : " << car.brand << endl;
                    cout << " Seri          : " << car.series << endl;
                    cout << " Warna         : " << car.color << endl;
                    cout << " Plat Nomor    : " << car.platNum << endl;
                    cout << " Tahun rilis   : " << car.release_year << endl;
                    cout << " Kapasitas     : " << car.capacity << endl;
                    cout << " Harga sewa    : " << "Rp " << car.price << endl;
                    cout << " Status        : " << (car.available ? "Tersedia" : "Tidak Tersedia") << endl;
                    cout << endl;
                    system("pause");
                    break;
                }
            }
            if (!ketemu) {
                cout << "Mobil dengan Plat Nomor atau Seri tersebut tidak ditemukan." << endl;
                system("pause");
            }
            break;
        case 2:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Cari konsumen
            system("cls");
            showHeaderBox("PENCARIAN DATA KONSUMEN");
            string keyword;
            cout << "Masukkan nama konsumen yang ingin dicari: ";
            cin.ignore();
            getline(cin, keyword);

            bool found = false;
            for (int i = 0; i <= stack.top; ++i) {
                if (stack.data[i].transferor_name.find(keyword) != string::npos) {
                    // Jika nama konsumen ditemukan, tampilkan detail transaksi
                    found = true;
                    cout << endl;
                    cout << "---- Informasi Pelanggan ----" << endl;
                    cout << " > Nama         : " << stack.data[i].transferor_name << endl;
                    cout << " > Nomor HP     : " << stack.data[i].phone_number << endl;
                    cout << " > Alamat       : " << stack.data[i].address << endl;
                    cout << " > NIK          : " << stack.data[i].NIK << endl;
                    cout << " > Pekerjaan    : " << stack.data[i].job << endl;
                    cout << "----- Detail Transaksi -----" << endl;
                    cout << " Waktu (dd/mm/yyyy) : " << stack.data[i].transaction_time << endl << endl;
                    cout << " Mobil yang disewa  : " << stack.data[i].car_rental_brand << " " << stack.data[i].car_rental_series << " " << stack.data[i].car_rental_release << " (" << stack.data[i].car_rental_platNum << ")" << endl;
                    cout << " Lama Sewa (hari)   : " << stack.data[i].duration << " hari" << endl;
                    cout << " Harga sewa         : " << stack.data[i].car_rental_price << " per hari" << endl;
                    cout << " Pembayaran         : " << stack.data[i].payment_method << endl;
                    cout << " Biaya Tambahan     : Rp " << stack.data[i].additional_fee << endl;
                    for (const auto& service : stack.data[i].additional_services) {
                        cout << "                      - " << service.name << "( Rp " << service.price << " )" << endl;
                    }
                    if (stack.data[i].discount != 0.0) {
                        cout << " Diskon 5%          : Rp " << stack.data[i].discount << endl;
                    }
                    cout << " Total Biaya        : Rp " << stack.data[i].amount << endl << endl;
                    break;
                }
            }

            if (!found) {
                cout << "Data konsumen dengan nama '" << keyword << "' tidak ditemukan." << endl;
            }

            system("pause");
            system("cls");
            break;
        }
    }
}
