#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

struct Buku {
    string id;    
    string judul;    
    string pengarang;
    string penerbit;
    int tahunTerbit;
    string genre;    
    int stok;
};

// Prototype Fungsi
void loadData(Buku buku[], int &jumlah);
void simpanData(Buku buku[], int jumlah);

void tampildata(Buku buku[], int jumlahdata);
void tambahbuku(Buku *buku, int &jumlahdata);
void editBuku(Buku buku[], int &jumlahData);
void cariNamaBuku(Buku buku[], int &jumlah);

string generateId(int &jumlahData);

int main() {

    Buku buku[100];
    int jumlahData = 0;

    loadData(buku, jumlahData);

    int pilihan = 0;
    
    cout << "Perpustakaan Mini" << endl;
    cout << "1. Pinjaman" << endl;
    cout << "2. Tambah buku" << endl;
    cout << "4. Test" << endl;
    
    do {
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if(pilihan == 1){
            tampildata(buku, jumlahData);
            
        } else if(pilihan == 2) {
            tambahbuku(&buku[jumlahData], jumlahData);
            
        } else if(pilihan == 3) {
            editBuku(buku, jumlahData);
            
        } else if(pilihan == 4) {
            cout << "Hapus Buku" << endl; // hapus ini jika kalian mengisi kondisi ini
            
        } else if(pilihan == 5){
            cariNamaBuku(buku, jumlahData);
            
        } else if(pilihan == 6){
            cout << "Pinjam Buku" << endl; // hapus ini jika kalian mengisi kondisi ini
            
        } else if(pilihan == 7){
            cout << "Kembalikan Buku" << endl; // hapus ini jika kalian mengisi kondisi ini 

        } else if(pilihan == 8){
            // simpan data manual
            simpanData(buku, jumlahData);
        
        } else if(pilihan == 9){
            // Simpan data otomatis ketika program berakhir
            simpanData(buku, jumlahData);            
            cout << "Terima kasih!" << endl;

        } else {
            cout << "Pilihan tidak tersedia" << endl;
        }
        
    } while (pilihan != 9);    
    
    return 0;
}

// Inisialisasi Fungsi -------------------------

void loadData(Buku buku[], int &jumlah) {
    ifstream file("data_buku.txt");    

    if (!file.is_open()){
        cout << "File tidak ditemukan atau gagal dibuka!" << endl;
        return;
    }
    while (!file.eof()) {        
        string tahunStr, stokStr;
        getline(file, buku[jumlah].id, '|');
        if (buku[jumlah].id == "") break;

        getline(file, buku[jumlah].judul, '|');
        getline(file, buku[jumlah].pengarang, '|');
        getline(file, buku[jumlah].penerbit, '|');
        getline(file, tahunStr, '|');        
        getline(file, buku[jumlah].genre, '|');
        getline(file, stokStr);                        

        buku[jumlah].tahunTerbit = stoi(tahunStr);
        buku[jumlah].stok = stoi(stokStr);

        jumlah++;
    }
    file.close();
}

// fungsi simpan data
void simpanData(Buku buku[], int jumlah) {
    ofstream file("data_buku.txt");

    if (!file) {
        cout << "Gagal membuka file untuk menyimpan data!" << endl;
        return;
    }

    for (int i = 0; i < jumlah; i++) {
        file << buku[i].id << "|"
             << buku[i].judul << "|"
             << buku[i].pengarang << "|"
             << buku[i].penerbit << "|"
             << buku[i].tahunTerbit << "|"
             << buku[i].genre << "|"
             << buku[i].stok << endl;
    }

    file.close();    
    cout << "\nData telah tersimpan.\n";
}

void tampildata(Buku buku[], int jumlahdata) {
    if(jumlahdata == 0){
        cout << "tidak ada data buku!" << endl;
        return;

    }

    cout << "\nDaftar Buku:" << endl;
    cout << left << setw(10) << "ID"
         << setw(20) << "judul"
         << setw(20) << "pengarang"
         << setw(20) << "penerbit"
         << setw(10) << "tahun"
         << setw(15) << "genre"
         << setw(5) << "stok" << endl;

    for(int i=0; i<jumlahdata; i++){
        cout << setw(10) << buku[i].id
             << setw(20) << buku[i].judul
             << setw(20) << buku[i].pengarang
             << setw(20) << buku[i].penerbit
             << setw(10) << buku[i].tahunTerbit
             << setw(15) << buku[i].genre
             << setw(5) << buku[i].stok << endl;
    }
}

void tambahbuku(Buku *buku, int &jumlahdata) {
    buku->id = generateId(jumlahdata);

    cout << "Masukkan Judul Buku: ";
    getline(cin, buku->judul);

    cout << "Masukkan Pengarang: ";
    getline(cin, buku->pengarang);

    cout << "Masukkan Penerbit: ";
    getline(cin, buku->penerbit);

    cout << "Masukkan Tahun Terbit: ";
    cin >> buku->tahunTerbit;
    cin.ignore();

    cout << "Masukkan Genre: ";
    getline(cin, buku->genre);

    cout << "Masukkan Stok Buku: ";
    cin >> buku->stok;
    cin.ignore();

    jumlahdata++;
    cout << "Buku berhasil ditambahkan!" << endl;
}

void editBuku(Buku buku[], int &jumlahData) {
    string cariNama;
    cout << "Masukkan Nama Buku yang dicari: ";
    getline(cin, cariNama);    
    
    int index = -1;
    
    for(int i = 0; i < jumlahData; i++) {
        if(buku[i].judul.find(cariNama) != string::npos) {
            index = i;
            break;
        }        
    }

    if(index == -1){
        cout << "Buku tidak ditemukan!" << endl;
        return;
    }

    cout << "Buku ditemukan!" << endl;
    cout << "Data Buku saat ini" << endl;
    cout << "ID                : " << buku[index].id << endl;
    cout << "Judul             : " << buku[index].judul << endl;
    cout << "Pengarang         : " << buku[index].pengarang << endl;
    cout << "Penerbit          : " << buku[index].penerbit << endl;
    cout << "Tahun Terbit      : " << buku[index].tahunTerbit << endl;
    cout << "Genre             : " << buku[index].genre << endl;
    cout << "Stok              : " << buku[index].stok << endl;

    string inputBaru;

    cout << "Masukkan judul baru: ";
    getline(cin, inputBaru);
    buku[index].judul = (inputBaru.empty()) ? buku[index].judul : inputBaru;
    
    cout << "Masukkan pengarang baru: ";
    getline(cin, inputBaru);
    buku[index].pengarang = (inputBaru.empty()) ? buku[index].pengarang : inputBaru;
    
    cout << "Masukkan penerbit baru: ";
    getline(cin, inputBaru);
    buku[index].penerbit = (inputBaru.empty()) ? buku[index].penerbit : inputBaru;
    
    cout << "Masukkan tahun terbit baru: ";
    getline(cin, inputBaru);
    buku[index].tahunTerbit = (inputBaru.empty()) ? buku[index].tahunTerbit : stoi(inputBaru);
    
    cout << "Masukkan genre baru: ";
    getline(cin, inputBaru);
    buku[index].genre = (inputBaru.empty()) ? buku[index].genre : inputBaru;
    
    cout << "Masukkan stok baru: ";
    getline(cin, inputBaru);
    buku[index].stok = (inputBaru.empty()) ? buku[index].stok : stoi(inputBaru);

    cout << "Data Buku telah diperbarui!" << endl;
}

void cariNamaBuku(Buku buku[], int &jumlah) {    
    string cariNama;
    cout << "Masukkan Nama Buku yang dicari: ";
    getline(cin, cariNama);

    bool ditemukan = false;

    cout << "Hasil Pencarian: " << endl;

    for (int i = 0; i < jumlah; i++) {
       
        if (buku[i].judul.find(cariNama) != string::npos) {
            cout << "ID                : " << buku[i].id << endl;
            cout << "Judul             : " << buku[i].judul << endl;
            cout << "Pengarang         : " << buku[i].pengarang << endl;
            cout << "Penerbit          : " << buku[i].penerbit << endl;
            cout << "Tahun Terbit      : " << buku[i].tahunTerbit << endl;
            cout << "Genre             : " << buku[i].genre << endl;
            cout << "Stok              : " << buku[i].stok << endl;
            
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << "Tidak ada Buku yang mengandung nama '" << cariNama << endl;
    }
}

string generateId(int &jumlahData) {
    stringstream ss;
    ss << "B" << setw(3) << setfill('0') << jumlahData + 1;
    return ss.str();
}
