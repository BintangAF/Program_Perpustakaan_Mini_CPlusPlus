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
void loaddata(Buku buku[], int&jumlah);
void simpanDataOtomatis(Buku buku[], int jumlah);

void tampildata(Buku buku[], int jumlahdata);
void tambahbuku(Buku *buku, int &jumlahdata);



int main() {

    Buku buku[100];
    int jumlahData = 0;

    loaddata (buku, jumlahData);

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
            cout << "Edit Buku" << endl; // hapus ini jika kalian mengisi kondisi ini
            
        } else if(pilihan == 4) {
            cout << "Hapus Buku" << endl; // hapus ini jika kalian mengisi kondisi ini
            
        } else if(pilihan == 5){
            cout << "Cari Buku" << endl; // hapus ini jika kalian mengisi kondisi ini
            
        } else if(pilihan == 6){
            cout << "Pinjam Buku" << endl; // hapus ini jika kalian mengisi kondisi ini
            
        } else if(pilihan == 7){
            cout << "Kembalikan Buku" << endl; // hapus ini jika kalian mengisi kondisi ini 

        } else if(pilihan == 8){
            cout << "Simpan Data" << endl; // hapus ini jika kalian mengisi kondisi ini
        
        } else if(pilihan == 9){
            cout << "Keluar" << endl; // hapus ini jika kalian mengisi kondisi ini

        } else {
            cout << "Pilihan tidak tersedia" << endl;
        }
        
    } while (pilihan != 9);

    simpanDataOtomatis(buku, jumlahData);
    
    return 0;
}

// Inisialisasi Fungsi -------------------------

void loaddata(Buku buku[], int&jumlah) {
    ifstream file("data_buku.txt");
    jumlah = 0;

    if (!file.is_open()){
        return;
    }
    while (!file.eof()) {
        Buku b;
        getline(file, b.id);
        if (b.id == "") break;

        getline(file, b.judul);
        getline(file, b.pengarang);
        getline(file, b.penerbit);
        file>> b.tahunTerbit;
        getline(file, b.genre);
        file>> b.stok;
        file.ignore();

        buku[jumlah] = b;
        jumlah++;
    }
}

// fungsi simpan otomatis
void simpanDataOtomatis(Buku buku[], int jumlah) {
    ofstream file("data_buku.txt");

    if (!file) {
        cout << "Gagal membuka file untuk menyimpan data otomatis!" << endl;
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
    cout << "\n(✓) Data otomatis disimpan sebelum program keluar.\n";
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
    cout << "\nMasukan ID Buku: ";
    getline(cin, buku[jumlahdata].id);

    cout << "Masukkan Judul Buku: ";
    getline(cin, buku[jumlahdata].judul);

    cout << "Masukkan Pengarang: ";
    getline(cin, buku[jumlahdata].pengarang);

    cout << "Masukkan Penerbit: ";
    getline(cin, buku[jumlahdata].penerbit);

    cout << "Masukkan Tahun Terbit: ";
    cin >> buku[jumlahdata].tahunTerbit;
    cin.ignore();

    cout << "Masukkan Genre: ";
    getline(cin, buku[jumlahdata].genre);

    cout << "Masukkan Stok Buku: ";
    cin >> buku[jumlahdata].stok;
    cin.ignore();

    jumlahdata++;
    cout << "Buku berhasil ditambahkan!" << endl;
}


